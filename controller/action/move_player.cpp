#include "move_player.h"

auto move_player::name() const -> std::string
{
	return "move-player";
}

auto move_player::description() const -> std::string
{
	return "Move other player's pawn (Dispatcher only)";
}

auto move_player::run(context & ctx, args_type const & args, ostream_type & out) const -> void
{
	try {

		auto movePlayer = args.at(0);	//player to move
		auto city = args.at(1);	//city to go to
		auto player = ctx.players.get_current_turn();    // Get the information of which player is playing
		auto currentCity = ctx.players.get_city(movePlayer);    // City movePlayer is currently on
		auto role = ctx.players.get_role(movePlayer);			// Get the role of movePlayer

		bool connected = false;

		if (ctx.players.get_role(player) != "dispatcher"_h) {
			out << "You are not a Dispatcher!" << std::endl;
			return;
		}
		
		//Teleport
		for (auto playerInCity : ctx.players) {
			if (city == ctx.players.get_city(playerInCity.first)) {
				ctx.players.set_city(movePlayer, city);
				// Check if the moved player is a medic
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
				out << "Teleport: " << movePlayer << " -> " << city << std::endl;
				return;
			}
		}

		//Drive
		for (auto connection = ctx.cities.begin(currentCity); connection != ctx.cities.end(currentCity); connection++) {
			if (*connection == city)
				connected = true;
		}

		if (connected) {
			ctx.players.set_city(movePlayer, city);                // Set the new position of player
			// Check if the moved player is a medic
			if (role == "medic"_h) {
				auto color = ctx.cities.get_color(city);
				if (ctx.game.discovered_cure(color)) {
					// If the cure is discovered, the medic remove all the cube without the cost of the action.
					int cubes = ctx.cities.get_cube_count(city, color);
					for (cubes; cubes > 0; cubes--) {
						ctx.cities.remove_cube(city, color);
						ctx.game.add_cube_to_supply(color);
					}
				}
			}
			ctx.players.decrement_actions_remaining();
			out << "Drive: " << movePlayer << " -> " << city << std::endl;
			return;
		}

		
		//Shuttle Flight
		if (ctx.cities.has_research_station(currentCity) == true) {
	
			if (ctx.cities.has_research_station(city) == true) {
				ctx.players.set_city(movePlayer, city);                // Set the new position of player
				// Check if the moved player is a medic
				if (role == "medic"_h) {
					auto color = ctx.cities.get_color(city);
					if (ctx.game.discovered_cure(color)) {
						// If the cure is discovered, the medic remove all the cube without the cost of the action.
						int cubes = ctx.cities.get_cube_count(city, color);
						for (cubes; cubes > 0; cubes--) {
							ctx.cities.remove_cube(city, color);
							ctx.game.add_cube_to_supply(color);
						}
					}
				}
				ctx.players.decrement_actions_remaining();
				out << "Shuttle flight: " << movePlayer << " -> " << city << std::endl;
				return;
			}
		}

		//Using Cards
		auto playerDiscard = "player_discard"_h;

		//Direct Flight
		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
			if (*card == city) {
				ctx.decks.remove(player, city);
				ctx.decks.add_to_top(playerDiscard, city);                // Add the card to the discard card deck
				ctx.players.set_city(movePlayer, city);                // Set the new position of player
				// Check if the moved player is a medic
				if (role == "medic"_h) {
					auto color = ctx.cities.get_color(city);
					if (ctx.game.discovered_cure(color)) {
						// If the cure is discovered, the medic remove all the cube without the cost of the action.
						int cubes = ctx.cities.get_cube_count(city, color);
						for (cubes; cubes > 0; cubes--) {
							ctx.cities.remove_cube(city, color);
							ctx.game.add_cube_to_supply(color);
						}
					}
				}
				ctx.players.decrement_actions_remaining();
				out << "Direct flight: " << movePlayer << " -> " << city << std::endl <<
					"Discarded " << city << " from " << player << "'s hand!" << std::endl;
				return;
			}
		}

		//Chartered Flight
		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
			if (*card == currentCity) {
				ctx.players.set_city(movePlayer, city);
				ctx.decks.remove(player, currentCity);
				ctx.decks.add_to_top(playerDiscard, currentCity);
				// Check if the moved player is a medic
				if (role == "medic"_h) {
					auto color = ctx.cities.get_color(city);
					if (ctx.game.discovered_cure(color)) {
						// If the cure is discovered, the medic remove all the cube without the cost of the action.
						int cubes = ctx.cities.get_cube_count(city, color);
						for (cubes; cubes > 0; cubes--) {
							ctx.cities.remove_cube(city, color);
							ctx.game.add_cube_to_supply(color);
						}
					}
				}
				ctx.players.decrement_actions_remaining();
				out << "Chartered flight: " << movePlayer << " -> " << city << std::endl <<
					"Discarded " << currentCity << " from " << player << "'s hand!" << std::endl;;
				return;
			}
		}

		out << "Move not possible!" << std::endl;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player> <city>" << std::endl;
	}



}
