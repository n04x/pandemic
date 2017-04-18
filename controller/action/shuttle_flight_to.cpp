#include "shuttle_flight_to.h"

auto shuttle_flight_to::name() const -> std::string {
	return "shuttle-flight-to";
}

auto shuttle_flight_to::description() const -> std::string {
	return "Fly to another city with a research station (Can only use if in city with research station)";
}

auto shuttle_flight_to::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto city = args.at(0);    // City flying to
		auto player = ctx.players.get_current_turn();		// Get the information of which player is playing
		auto currentCity = ctx.players.get_city(player);    // City player is currently on
		auto role = ctx.players.get_role(player);			// Get the role of the player.

		if (ctx.cities.has_research_station(currentCity) == false) {
			out << "Current city player is in does not have a research station!" << std::endl;
			return;
		}
		
		if (ctx.cities.has_research_station(city) == false) {

			// Check if the player is the Operation Expert, he can fly to anywhere from a research station.
			if (role == "operations_expert"_h) {

				try {
					auto removeCard = args.at(1);
					auto playerDiscard = "player_discard"_h;

					for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
						if (*card == removeCard) {
							ctx.players.set_city(player, city);					// Set the new position of player
							ctx.decks.remove(player, removeCard);				// Remove card from player hand
							ctx.decks.add_to_top(playerDiscard, removeCard);				// Add to discard
							ctx.players.decrement_actions_remaining();
							out << "Shuttle flight: " << player << " -> " << city << " [Operations Expert]" << std::endl
								<< "Discarded " << removeCard << " from " << player << "'s hand!" << std::endl;
							return;
						}
					}

					out << removeCard << " is not in " << player << "'s hand!" << std::endl;
					return;
				}
				catch (std::out_of_range const &) {
					out << "usage: " << name() << " <city> <card_to_remove>" << std::endl;
					return;
				}
			}

			out << "City flying to does not have a research station!" << std::endl;
			return;
		}

		ctx.players.set_city(player, city);                // Set the new position of player
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
		ctx.players.decrement_actions_remaining();
		out << "Shuttle flight: " << player << " -> " << city << std::endl;
		return;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <city>" << std::endl;
	}
}
