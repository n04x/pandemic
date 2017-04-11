#include "place_research_station.h"

auto place_research_station::name() const -> std::string {
	return "place-research-station";
}

auto place_research_station::description() const -> std::string {
	return "Place a research station on map";
}

auto place_research_station::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto city = args.at(0);								// Renamed for name to city for clarification
		auto player = ctx.players.get_current_turn();		// Current turn of the player
		auto role = ctx.players.get_role(player);			// Check the player role.

		if (ctx.cities.has_research_station(city) == false) {
			// If the player is the Ops Expert AND is in the same city as requested.
			if (role == "operation_expert"_h && city == ctx.players.get_city(player)) {
				ctx.game.remove_research_station_supply();
				ctx.cities.place_research_station(city);
				ctx.players.decrement_actions_remaining();
			}
			else {
				if (city == ctx.players.get_city(player)) {
					for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
						if (*card == city) {
							ctx.game.remove_research_station_supply();
							ctx.cities.place_research_station(city);
							ctx.players.decrement_actions_remaining();
						}
					}
					
				}
				
			}
			
		}

	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<city>" << std::endl;
	}
}