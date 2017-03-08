#include "move_top_card.h"


auto move_top_card::name() const -> std::string
{
	return "move-top-card";
}

auto move_top_card::description() const -> std::string
{
	return "Moves the top card";
}

auto move_top_card::run(context & ctx, args_t const & args, ostream_t & out) const -> void
{
	try {
		auto fromDeck = args.at(0);
		auto toDeck = args.at(1);

		auto topCard = ctx.decks.remove_from_top(fromDeck);

		ctx.decks.add_to_top(toDeck, topCard);
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <fromDeck> <toDeck>" << std::endl;
	}
}
