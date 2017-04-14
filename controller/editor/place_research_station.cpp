#include "place_research_station.h"

auto place_research_station::name() const -> std::string {
	return "place-research-station";
}

auto place_research_station::description() const -> std::string {
	return "Place a research station on map";
}

auto place_research_station::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	
	if (args.empty()) {

		auto player = ctx.players.get_current_turn();		// Current turn of the player
		auto city = ctx.players.get_city(player);			// Renamed for name to city for clarification
		auto role = ctx.players.get_role(player);			// Check the player role.
		
		if (ctx.cities.has_research_station(city) == false) {
			
			// If the player is the Ops Expert AND is in the same city as requested.
			if (role == "operation_expert"_h) {
				ctx.game.remove_research_station_supply();
				ctx.cities.place_research_station(city);
				ctx.players.decrement_actions_remaining();
				return;
			}

			else {
				for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
					if (*card == city) {
						ctx.decks.remove(player, city);
						ctx.game.remove_research_station_supply();
						ctx.cities.place_research_station(city);
						ctx.players.decrement_actions_remaining();
						return;
					}
				}
			}

			out << "You do not have the " << city << " card in your hand!" << std::endl;
			return;
		}

		else {
			out << city << " already has a reasearch station!" << std::endl;
			return;
		}
	}

	//To be used when setting up board
	try {

		auto city = args.at(0);								// Renamed for name to city for clarification

		ctx.game.remove_research_station_supply();
		ctx.cities.place_research_station(city);

	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <city>" << std::endl;
	}
}