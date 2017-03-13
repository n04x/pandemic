#include "create_deck.h"

auto create_deck::name() const -> std::string {
	return "create-deck";
}

auto create_deck::description() const -> std::string {
	return "Creates a new card deck";
}

auto create_deck::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto name = args.at(0);
		ctx.decks.create(name);
	} catch (std::out_of_range const &) {
		out << "usage: " << name() << " <deck>" << std::endl;
	}
}
