#include "draw_turn.h"

auto draw_turn::name() const -> std::string
{
	return "draw-turn";
}

auto draw_turn::description() const -> std::string
{
	return "Draw 2 cards into player's hand";
}

auto draw_turn::run(context & ctx, args_t const & args, ostream_t & out) const -> void
{

	try {
		auto cardOne = ctx.decks.remove_from_top(args.at(0));
		auto cardTwo = ctx.decks.remove_from_top(args.at(0));

		auto currentPlayer = ctx.players.get_current_turn();

		ctx.decks.add_to_top(currentPlayer, cardOne);
		ctx.decks.add_to_top(currentPlayer, cardTwo);
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player_deck>" << std::endl;
	}

}
