#include "share_knowledge_to.h"

auto share_knowledge_to::name() const -> std::string {
	return "share-knowledge-to";
}

auto share_knowledge_to::description() const -> std::string {
	return "Give player card of city both players are in to other player";
}

static auto hand_limit(context &ctx, share_knowledge_to::ostream_type &out, handle player) -> void {
	static const auto limit = 7;
	if (ctx.decks.size(player) > limit) {
		auto card = ctx.decks.remove_from_bottom(player);
		ctx.decks.add_to_top("player_discard"_h, card);
		out << "'" << player << "' player reached hand limit, discarding '" << card << "'" << std::endl;
	}
}

auto share_knowledge_to::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto playerOne = ctx.players.get_current_turn();
		auto playerTwo = args.at(0);
		auto chosenCard = args.at(1);
		auto city = ctx.players.get_city(playerOne);
		auto p1Role = ctx.players.get_role(playerOne);		// Get the player One role since he is the one who give his card.
		
		if (!(city == ctx.players.get_city(playerTwo))) {
			out << "Players not in the same city!" << std::endl;
			return;
		}
		// If the player one is a researcher, he can gives any card he wants.
		else if (p1Role == "researcher"_h) {
			
			for (auto card = ctx.decks.begin(playerOne); card != ctx.decks.end(playerOne); card++) {
				if (*card == chosenCard) {
					ctx.decks.remove(playerOne, chosenCard);
					ctx.decks.add_to_top(playerTwo, chosenCard);
					hand_limit(ctx, out, playerTwo);
					ctx.players.decrement_actions_remaining();
					return;
				}
			}
		}
		else {
				for (auto card = ctx.decks.begin(playerOne); card != ctx.decks.end(playerOne); card++) {
					if (*card == city) {
						ctx.decks.remove(playerOne, city);
						ctx.decks.add_to_top(playerTwo, city);
						hand_limit(ctx, out, playerTwo);
						ctx.players.decrement_actions_remaining();
						return;
					}
				}
		}
		out << playerOne << " does not have city card!" << std::endl;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player> [city]" << std::endl;
	}
}
