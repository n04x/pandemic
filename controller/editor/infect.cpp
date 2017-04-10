#include "infect.h"

auto infect::name() const -> std::string {
	return "infect";
}

auto infect::description() const -> std::string {
	return "infect a city";
}

auto infect::run(context &ctx, const args_type &args, ostream_type &out) const -> void {
	try {
		auto player = ctx.players.get_current_turn();
		auto infection_deck = args.at(0);
		auto discard_deck = args.at(1);
		auto cube_count = stoi(args.at(2));
		auto city_infected_name = ctx.decks.remove_from_top(infection_deck);        // Draw the city card to infect
		auto city_infected_color = ctx.cities.get_color(city_infected_name);        // get the color of the city to infect
		ctx.cities.add_cube(city_infected_name, city_infected_color, cube_count);    // Add the cube to the infected city
		ctx.game.remove_cube_from_supply(city_infected_color, cube_count);            // Remove these cube from supply
		ctx.decks.add_to_top(discard_deck, city_infected_name);                        // Put the city card in the discard deck

	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<infection_deck> <discard_deck> <cube_count>" << std::endl;
	}
}