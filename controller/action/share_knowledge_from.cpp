#include "share_knowledge_from.h"

auto share_knowledge_from::name() const -> std::string
{
	return "share-knowledge-from";
}

auto share_knowledge_from::description() const -> std::string
{
	return "Take player card of city both players are in to other player";
}

auto share_knowledge_from::run(context & ctx, args_t const & args, ostream_t & out) const -> void
{
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
