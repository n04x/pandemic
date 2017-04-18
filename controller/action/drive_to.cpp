#include "drive_to.h"

auto drive_to::name() const -> std::string {
	return "drive-to";
}

auto drive_to::description() const -> std::string {
	return "Drive to city selected";
}

auto drive_to::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto city = args.at(0);
		auto player = ctx.players.get_current_turn();    // Get the information of which player is playing
		auto currentCity = ctx.players.get_city(player);    // City player is currently on
		auto role = ctx.players.get_role(player);

		bool connected = false;

		for (auto connection = ctx.cities.begin(currentCity); connection != ctx.cities.end(currentCity); connection++) {
			if (*connection == city)
				connected = true;
		}

		if (connected) {
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
			out << "Drive: " << player << " -> " << city << std::endl;
		} else
			out << city << " is not possible to drive to from " << currentCity << std::endl;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <city>" << std::endl;
	}
}
