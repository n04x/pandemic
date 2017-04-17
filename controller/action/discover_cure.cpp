#include "discover_cure.h"

auto discover_cure::name() const -> std::string {
	return "discover-cure";
}

auto discover_cure::description() const -> std::string {
	return "At any research station, discard 5 City cards of the same color from your hand to cure the disease of that color";
}

auto discover_cure::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	auto discardDeck = "player_discard"_h;
	
	try {
		auto color = args.at(0);
		auto player = ctx.players.get_current_turn();
		auto city = ctx.players.get_city(player);
		if (!ctx.cities.has_research_station(city)) {
			out << "'" << city << "' has no research station" << std::endl;
			return;
		}

		auto role = ctx.players.get_role(player);
		if (args.size() > 1) {
			discardDeck = args.at(1);
		}

		if (ctx.game.discovered_cure(color)) {
			out << color << " already cured!" << std::endl;
			return;
		}

		std::vector<handle> v;	

		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
			if (ctx.cities.get_color(*card) == color) {
				v.push_back(*card);
			}
			// It will check the role of the user with the role in the condition
			if (role == "scientist"_h) {
				// The Scientist needs only 4 City cards of the same disease color to Discover a Cure for that disease.
				if (v.size() == 4) {
					for (int i = 0; i < v.size(); i++) {
						ctx.decks.remove(player, v[i]);
						ctx.decks.add_to_top(discardDeck, v[i]);
					}
					ctx.game.discovered_cure(color);
					ctx.players.decrement_actions_remaining();

					out << "Cure for " << color << " has been discovered! [Scientist]" << std::endl;

					return;
				}
			}
			// Else if the player is not a scientist.
			else if (v.size() == 5) {
				for (int i = 0; i < v.size(); i++) {
					ctx.decks.remove(player, v[i]);
					ctx.decks.add_to_top(discardDeck, v[i]);
				}

				ctx.game.discover_cure(color);
				ctx.players.decrement_actions_remaining();

				out << "Cure for " << color << " has been discovered!" << std::endl;

				return;
			}
		}

		out << "Not enough " << color << " cards in " << player << "'s hand!" << std::endl;

	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <color> [discard_deck]" << std::endl;
	}
}
