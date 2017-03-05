#include "add_to_deck.h"

auto add_to_deck::name() const -> std::string {
	return "add-to-deck";
}

auto add_to_deck::description() const -> std::string {
	return "Add to the deck";
}

auto add_to_deck::run(context &ctx, args_t const &args, ostream_t &out) const -> void {
	try {
		auto deckName = args.at(0);
		auto cardName = args.at(1);
		ctx.decks.add_to_top(deckName, cardName);
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<deck>" << std::endl;
	}
}