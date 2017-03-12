#include "share_knowledge_to.h"

auto share_knowledge_to::name() const -> std::string
{
	return "share-knowledge-to";
}

auto share_knowledge_to::description() const -> std::string
{
	return "Give player card of city both players are in to other player";
}

auto share_knowledge_to::run(context & ctx, args_t const & args, ostream_t & out) const -> void
{
	try {
		auto playerOne = ctx.players.get_current_turn();
		auto playerTwo = args.at(0);
		auto city = ctx.players.get_city(playerOne);

		if (!(city == ctx.players.get_city(playerTwo))) {
			out << "Players not in the same city!" << std::endl;
			return;
		}

		for (auto card = ctx.decks.begin(playerOne); card != ctx.decks.end(playerOne); card++) {
			if (*card == city) {
				ctx.decks.remove(playerOne, city);
				ctx.decks.add_to_top(playerTwo, city);
				return;
			}
		}

		out << playerOne << " does not have city card!" << std::endl;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player>" << std::endl;
	}
}
