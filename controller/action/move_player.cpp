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
		
		//TODO Teleport to other player
		/*		Checks to see if city has a player in it a moves movePlayer to that city
		if (city == ctx.cities.has_player()) {
			ctx.players.set_city(movePlayer, city);
			ctx.players.decrement_actions_remaining();
			out << "Teleported" << std::endl;
			return;
		}
		*/	

		//Drive
		for (auto connection = ctx.cities.begin(currentCity); connection != ctx.cities.end(currentCity); connection++) {
			if (*connection == city)
				connected = true;
		}

		if (connected) {
			ctx.players.set_city(movePlayer, city);                // Set the new position of player
			ctx.players.decrement_actions_remaining();
			out << "Drive: " << movePlayer << " -> " << city << std::endl;
			return;
		}

		
		//Shuttle Flight
		if (ctx.cities.has_research_station(currentCity) == true) {	//TODO test when place-research-station is fixed
			
			/*				Can dispatcher move operation expert like operation expert?
			// Check if the player is the Operation Expert, he can fly to anywhere from a research station.
			if (role == "operation_expert"_h) {
				ctx.players.set_city(movePlayer, city);                // Set the new position of player
				ctx.players.decrement_actions_remaining();
				out << "Shuttle flight: " << movePlayer << " -> " << city << " [Operation Expert]" << std::endl;
				return;
			}
			*/

			if (ctx.cities.has_research_station(city) == true) {
				ctx.players.set_city(movePlayer, city);                // Set the new position of player
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
				ctx.players.decrement_actions_remaining();
				out << "Direct flight: " << movePlayer << " -> " << city << std::endl;
				return;
			}
		}

		//Chartered Flight
		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
			if (*card == currentCity) {
				ctx.players.set_city(movePlayer, city);
				ctx.decks.remove(player, currentCity);
				ctx.decks.add_to_top(playerDiscard, currentCity);
				ctx.players.decrement_actions_remaining();
				out << "Chartered flight: " << movePlayer << " -> " << city << std::endl;
				return;
			}
		}

		out << "Move not possible!" << std::endl;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<player> <city>" << std::endl;
	}



}
