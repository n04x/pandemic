#include "play_event.h"


auto play_event::name() const -> std::string
{
	return "play-event";
}

auto play_event::description() const -> std::string
{
	return "Play event";
}

auto play_event::run(context & ctx, args_type const & args, ostream_type & out) const -> void
{
	try {
		auto event = args.at(0);
		auto player = ctx.players.get_current_turn();
		auto playerDiscard = "player_discard"_h;
		auto infectionDiscard = "infection_discard"_h;

		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
			if (*card == event) {

				if (event == "airlift"_h) {
					try {
						auto playerMove = args.at(1);
						auto city = args.at(2);

						ctx.players.set_city(playerMove, city);                // Set the new position of player
						ctx.decks.remove(player, event);
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " airlift <player> <city>" << std::endl;
					}
				}

				if (event == "forecast"_h) {
					try {
					
						//TODO Forecast event card
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " forecast" << std::endl;
					}

				}

				if (event == "government_grant"_h) {
					try {
						auto city = args.at(1);

						if (ctx.cities.has_research_station(city) == false) {
							ctx.game.remove_research_station_supply();
							ctx.cities.place_research_station(city);
							ctx.decks.remove(player, event);
						}

						else
							out << "City already has a research station!" << std::endl;
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " government_grant <city>" << std::endl;
					}
				}

				if (event == "one_quiet_night"_h) {

					try {
					
						//TODO One Quiet Night
						
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " one_quiet_night" << std::endl;
					}

				}

				if (event == "resilient_population"_h) {

					try {
						auto infCard = args.at(1);
						
						for (auto card = ctx.decks.begin(infectionDiscard); card != ctx.decks.end(infectionDiscard); card++) {
							if (*card == infCard) {
								ctx.decks.remove(infectionDiscard, infCard);
								ctx.decks.remove(player, event);
								return;
							}
						}

						out << infCard << " is not in the infection discard pile!" << std::endl;
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " resilient_population <card_to_remove>" << std::endl;
					}

				}

				ctx.decks.add_to_top(playerDiscard, event);
				return;
			}


		}

		out << "Event card not found in " << ctx.players.get_current_turn() << "'s hand!" << std::endl;

	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <card_name>" << std::endl;
	}

}
