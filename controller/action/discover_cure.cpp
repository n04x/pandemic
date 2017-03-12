#include "discover_cure.h"

auto discover_cure::name() const -> std::string
{
	return "discover-cure";
}

auto discover_cure::description() const -> std::string
{
	return "At any research station, discard 5 City cards of the same color from your hand to cure the disease of that color";
}

auto discover_cure::run(context & ctx, args_t const & args, ostream_t & out) const -> void
{
	try {
		auto color = args.at(0);
		auto player = ctx.players.get_current_turn();
		auto discardDeck = args.at(1);

		if (ctx.game.discovered_cure(color)) {
			out << color << " already cured!" << std::endl;
			return;
		}
		
		std::vector<handle> v;

		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
			if (ctx.cities.get_color(*card) == color) {
				v.push_back(*card);
			}

			if (v.size() == 5) {
				for (int i = 0; i < v.size(); i++) {
					ctx.decks.remove(player, v[i]);
					ctx.decks.add_to_top(discardDeck, v[i]);
				}

				ctx.game.discover_cure(color);
				ctx.players.decrement_actions_remaining();

				return;
			}
		}
		
		out << "Not enough " << color << " cards in hand!" << std::endl;

	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <color> <discard_deck>" << std::endl;
	}
}
