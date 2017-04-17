#include "treat_disease.h"

auto treat_disease::name() const -> std::string {
	return "treat-disease";
}

auto treat_disease::description() const -> std::string {
	return "Remove 1 disease cub from city player is in";
}

auto treat_disease::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto player = ctx.players.get_current_turn();   // Current turn player
		auto city = ctx.players.get_city(player);		// Current city player wants to treat
		auto role = ctx.players.get_role(player);		// Get the player role
		auto color = args.at(0);						// Color cube to remove					

		if (ctx.cities.get_cube_count(city, color) == 0) {
			out << "There are no " << color << " cubes in " << city << "!" << std::endl;
			return;
		}
		// It will check the role of the user with the role in the condition
		if (role == "medic"_h) {
			// The Medic removes all cubes, not 1, of the same color when doing the Treat Disease action.
			int cubes = ctx.cities.get_cube_count(city, color);
			for (cubes; cubes > 0; cubes--) {
				ctx.cities.remove_cube(city, color);
				ctx.game.add_cube_to_supply(color);
			}
			ctx.players.decrement_actions_remaining();
			out << "Removed all " << color << " cubes from " << city << "! [Medic]" << std::endl;
		}
		else {
			ctx.cities.remove_cube(city, color);
			ctx.game.add_cube_to_supply(color);
			ctx.players.decrement_actions_remaining();
			out << "Removed one " << color << " cube from " << city << "!" << std::endl;
		}
	}

	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <color>" << std::endl;
	}
}
