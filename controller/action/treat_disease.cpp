#include "treat_disease.h"

auto treat_disease::name() const -> std::string
{
	return "treat-disease";
}

auto treat_disease::description() const -> std::string
{
	return "Remove 1 disease cub from city player is in";
}

auto treat_disease::run(context & ctx, args_t const & args, ostream_t & out) const -> void
{
	try {
		auto player = ctx.players.get_current_turn();	// Current turn player
		auto city = ctx.players.get_city(player);	// Current city player wants to treat
		auto color = args.at(0);	// Color cube to remove

		if (ctx.cities.get_cube_count(city, color) == 0) {
			out << "There exists no " << color << " cubes in " << city << "!" << std::endl;
			return;
		}

		ctx.cities.remove_cube(city, color);
	}

	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <color>" << std::endl;
	}
}
