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
		auto city = ctx.players.get_city(playerOne);

		if (!(city == ctx.players.get_city(playerTwo))) {
			out << "Players not in the same city!" << std::endl;
			return;
		}

		for (auto card = ctx.decks.begin(playerTwo); card != ctx.decks.end(playerTwo); card++) {
			if (*card == city) {
				ctx.decks.remove(playerTwo, city);
				ctx.decks.add_to_top(playerOne, city);
				hand_limit(ctx, out, playerOne);
				ctx.players.decrement_actions_remaining();
				return;
			}
		}

		out << playerTwo << " does not have city card!" << std::endl;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player>" << std::endl;
	}


}
