#include "add_cities_to_deck.h"

auto add_cities_to_deck::name() const -> std::string {
	return "add-cities-to-deck";
}

auto add_cities_to_deck::description() const -> std::string {
	return "Add a cities to the deck";
}

auto add_cities_to_deck::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto name = args.at(0);
		for (auto city : ctx.cities) {
			ctx.decks.add_to_top(name, city.first);
		}
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<deck>" << std::endl;
	}
}