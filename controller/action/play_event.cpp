#include "play_event.h"
#include <iterator>
#include <algorithm>

auto play_event::name() const -> std::string
{
	return "play-event";
}

auto play_event::description() const -> std::string
{
	return "Play event card from any player's hand (Does not count as a action)";
}

auto play_event::run(context & ctx, args_type const & args, ostream_type & out) const -> void
{
	try {
		auto player = args.at(0);	//Player with event card
		auto event = args.at(1);	//Event card
		auto playerDiscard = "player_discard"_h;
		auto infectionDiscard = "infection_discard"_h;
		auto infectionDeck = "infection"_h;

		//If player is a Contingency Planner check contingency planner deck
		auto cardFound = std::find(ctx.decks.begin(player), ctx.decks.end(player), event) != ctx.decks.end(player);
		if (!cardFound && ctx.players.get_role(player) == "contingency_planner"_h) {
			player = "contingency_planner";
		}

		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {	//Check all cards in player's hand
			if (*card == event) {	//if card found

				if (event == "airlift"_h) {
					try {
						auto playerMove = args.at(2);	//Player to move
						auto city = args.at(3);	//City to go to

						ctx.players.set_city(playerMove, city);	// Set the new position of player
						ctx.decks.remove(player, event);

						// Handle medic cures
						auto role = ctx.players.get_role(playerMove);
						if (role == "medic"_h) {
							static const std::vector<handle> colors = {"black"_h, "blue"_h, "yellow"_h, "red"_h};
							for (auto color : colors) {
								if (ctx.game.discovered_cure(color)) {
									// If the cure is discovered, the medic remove all the cube without the cost of the action.
									int cubes = ctx.cities.get_cube_count(city, color);
									for (cubes; cubes > 0; cubes--) {
										ctx.cities.remove_cube(city, color);
										ctx.game.add_cube_to_supply(color);
									}
								}
							}
						}

						if (player != "contingency_planner")
							ctx.decks.add_to_top(playerDiscard, event);

						out << "Airlift: " << playerMove << " -> " << city << std::endl;
						
						if (player != "contingency_planner") {
							out << "Discarded " << event << " from " << player << "'s hand!" << std::endl;
							return;
						}

						out << "Removed " << event << " from play!" << std::endl;
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " <player_with_card> airlift <player_to_move> <city>" << std::endl;
					}
				}

				if (event == "forecast"_h) {
					static const auto amount = 6;
					try {
						// Get top 6 cards in infection deck
						std::vector<handle> top6;
						std::copy_n(ctx.decks.begin("infection"_h), std::min(std::size_t{ 6 }, ctx.decks.size("infection"_h)), std::back_inserter(top6));
						if (top6.size() != amount) {
							out << name() << ": not enough cards in infection deck";
							return;
						}

						// Get target order
						std::vector<handle> target6;
						auto iterator = args.begin();
						iterator++;
						iterator++;
						std::copy(iterator, args.end(), std::back_inserter(target6));
						if (target6.size() != amount) {
							out << "usage: " << name() << " <player_with_card> forecast <1> <2> <3> <4> <5> <6>" << std::endl;
							return;
						}

						// Ensure the target cards exist in the top of infection deck
						std::vector<handle> top6_sorted{top6};
						std::vector<handle> target6_sorted{target6};
						std::sort(top6_sorted.begin(), top6_sorted.end());
						std::sort(target6_sorted.begin(), target6_sorted.end());
						std::vector<handle> intersection;
						std::set_difference(top6_sorted.begin(), top6_sorted.end(), target6_sorted.begin(), target6_sorted.end(), std::back_inserter(intersection));
						if (!intersection.empty()) {
							out << name() << ": cards not at top of infection deck";
							return;
						}

						// Re-order the cards
						for (auto i = 0; i < amount; i++) {
							ctx.decks.remove_from_top("infection"_h);
						}
						for (auto i = target6.rbegin(); i != target6.rend(); i++) {
							ctx.decks.add_to_top("infection"_h, *i);
						}

						ctx.decks.remove(player, event);

						if (player != "contingency_planner")
							ctx.decks.add_to_top(playerDiscard, event);


						if (player != "contingency_planner") {
							out << "Discarded " << event << " from " << player << "'s hand!" << std::endl;
							return;
						}

						out << "Removed " << event << " from play!" << std::endl;

					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " <player_with_card> forecast <1> <2> <3> <4> <5> <6>" << std::endl;
					}

				}

				if (event == "government_grant"_h) {
					try {
						auto city = args.at(2);	//City to add research station

						if (ctx.cities.has_research_station(city) == false) {	//Check if research station exists
							ctx.game.remove_research_station_supply();
							ctx.cities.place_research_station(city);
							ctx.decks.remove(player, event);

							if (player != "contingency_planner")
								ctx.decks.add_to_top(playerDiscard, event);

							out << "Placed research station in " << city << "!" << std::endl;

							if (player != "contingency_planner") {
								out << "Discarded " << event << " from " << player << "'s hand!" << std::endl;
								return;
							}

							out << "Removed " << event << " from play!" << std::endl;
						}

						else
							out << "City already has a research station!" << std::endl;
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " <player_with_card> government_grant <city>" << std::endl;
					}
				}

				if (event == "one_quiet_night"_h) {

					try {

						ctx.players.skip_next_infection_phase();
						ctx.decks.remove(player, event);
						
						if (player != "contingency_planner")
							ctx.decks.add_to_top(playerDiscard, event);

						if (player != "contingency_planner") {
							out << "Discarded " << event << " from " << player << "'s hand!" << std::endl;
							return;
						}

						out << "Removed " << event << " from play!" << std::endl;

					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " <player_with_card> one_quiet_night" << std::endl;
					}

				}

				if (event == "resilient_population"_h) {

					try {
						auto infCard = args.at(2);	//Infection card to remove from play
						
						for (auto card = ctx.decks.begin(infectionDiscard); card != ctx.decks.end(infectionDiscard); card++) {
							if (*card == infCard) {
								ctx.decks.remove(infectionDiscard, infCard);	//Completely remove from play card
								ctx.decks.remove(player, event);
								
								if (player != "contingency_planner")
									ctx.decks.add_to_top(playerDiscard, event);

								out << "Removed " << infCard << " from play!" << std::endl;

								if (player != "contingency_planner") {
									out << "Discarded " << event << " from " << player << "'s hand!" << std::endl;
									return;
								}

								out << "Removed " << event << " from play!" << std::endl;
							}
						}

						out << infCard << " is not in the infection discard pile!" << std::endl;	//If no card found
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " <player_with_card> resilient_population <card_to_remove>" << std::endl;
					}
				}

				return;
			}

		}

		out << event <<" card not found in " << player << "'s hand!" << std::endl;	//If card not found
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player_with_card> <card_name>" << std::endl;
	}

}
