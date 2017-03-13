#include "draw_turn.h"

auto draw_turn::name() const -> std::string {
	return "draw-turn";
}

auto draw_turn::description() const -> std::string {
	return "Draw 2 cards into player's hand";
}

auto draw_turn::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	auto playerDeck = "player"_h;
	try {
		if (!args.empty()) {
			playerDeck = args.at(0);
		}
		auto cardOne = ctx.decks.remove_from_top(playerDeck);
		auto cardTwo = ctx.decks.remove_from_top(playerDeck);

		auto currentPlayer = ctx.players.get_current_turn();

		ctx.decks.add_to_top(currentPlayer, cardOne);
		out << "'" << cardOne << "' added to your hand" << std::endl;
		ctx.decks.add_to_top(currentPlayer, cardTwo);
		out << "'" << cardTwo << "' added to your hand" << std::endl;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " [player_deck]" << std::endl;
	}

}
