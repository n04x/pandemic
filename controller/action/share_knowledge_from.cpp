#include "share_knowledge_from.h"

auto share_knowledge_from::name() const -> std::string {
	return "share-knowledge-from";
}

auto share_knowledge_from::description() const -> std::string {
	return "Take player card of city both players are in to other player";
}

static auto hand_limit(context &ctx, share_knowledge_from::ostream_type &out, handle player) -> void {
	static const auto limit = 7;
	if (ctx.decks.size(player) > limit) {
		auto card = ctx.decks.remove_from_bottom(player);
		ctx.decks.add_to_top("player_discard"_h, card);
		out << "'" << player << "' player reached hand limit, discarding '" << card << "'" << std::endl;
	}
}

auto share_knowledge_from::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto playerOne = ctx.players.get_current_turn();
		auto playerTwo = args.at(0);
		auto chosenCard = args.at(1);
		auto p2Role = ctx.players.get_role(playerTwo);
		auto city = ctx.players.get_city(playerOne);

		if (!(city == ctx.players.get_city(playerTwo))) {
			out << "Players not in the same city!" << std::endl;
			return;
		}
		// If the player two is a researcher, player one can takes any card player one wants.
		else if(p2Role == "researcher"_h) { 
			for (auto card = ctx.decks.begin(playerTwo); card != ctx.decks.end(playerTwo); card++) {
				if (*card == chosenCard) {
					ctx.decks.remove(playerTwo, chosenCard);
					ctx.decks.add_to_top(playerOne, chosenCard);
					hand_limit(ctx, out, playerOne);
					ctx.players.decrement_actions_remaining();
					out << chosenCard << " taken from " << playerTwo << " to " << playerOne << "! [Researcher]" << std::endl;
					return;
				}
			}
		}
		else {

			if (!(city == chosenCard)) {
				out << "You are not in " << chosenCard << "!" << std::endl;
				return;
			}

			for (auto card = ctx.decks.begin(playerTwo); card != ctx.decks.end(playerTwo); card++) {
				if (*card == city) {
					ctx.decks.remove(playerTwo, city);
					ctx.decks.add_to_top(playerOne, city);
					hand_limit(ctx, out, playerOne);
					ctx.players.decrement_actions_remaining();
					out << chosenCard << " taken from " << playerTwo << " to " << playerOne << "!" << std::endl;
					return;
				}
			}
		}

		out << playerTwo << " does not have " << city << " card!" << std::endl;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player> [city]" << std::endl;
	}


}
