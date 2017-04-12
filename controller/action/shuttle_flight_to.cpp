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
		// Check if the player is the Operation Expert, he can fly to anywhere from a research station.
		if (role == "operation_expert"_h) {
			ctx.players.set_city(player, city);                // Set the new position of player
			ctx.players.decrement_actions_remaining();
			return;
		}
		else {
			if (ctx.cities.has_research_station(city) == false) {
				out << "City flying to does not have a research station!" << std::endl;
				return;
			}

			ctx.players.set_city(player, city);                // Set the new position of player
			ctx.players.decrement_actions_remaining();
		}
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <city>" << std::endl;
	}
}
