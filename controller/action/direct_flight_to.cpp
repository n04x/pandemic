#include "direct_flight_to.h"

auto direct_flight_to::name() const -> std::string {
	return "direct-flight-to";
}

auto direct_flight_to::description() const -> std::string {
	return "Direct Flight To ...";
}

auto direct_flight_to::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	auto discard_deck = "player_discard"_h;
	try {
		auto city = args.at(0);
		auto player = ctx.players.get_current_turn();    // Get the information of which player is playing

		if (args.size() > 1) {
			discard_deck = args.at(1);
		}
		auto role = ctx.players.get_role(player);

		if (role == "medic"_h) {
			static const std::vector<handle> colors = {"black"_h, "blue"_h, "yellow"_h, "red"_h};
			for (auto color : colors) {
				if (ctx.game.discovered_cure(color)) {
					// If the cure is discovered, the medic remove all the cube without the cost of the action.
					int cubes = ctx.cities.get_cube_count(city, color);
					for (cubes; cubes > 0; cubes--) {
						ctx.cities.remove_cube(city, color);
						ctx.game.add_cube_to_supply(color);
					}
				}
			}
		}
		ctx.players.decrement_actions_remaining();
		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
			if (*card == city) {
				ctx.decks.remove(player, city);
				ctx.decks.add_to_top(discard_deck, city);                // Add the card to the discard card deck
				ctx.players.set_city(player, city);                // Set the new position of player
				ctx.players.decrement_actions_remaining();
				out << "Direct flight: " << player << " -> " << city << std::endl
					<< "Discarded " << city << " from " << player << "'s hand!" << std::endl;
				return;
			}
		}
		
		out << city << " is not in " << player << "'s hand!" << std::endl;
		return;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <city> [discard_deck]" << std::endl;
	}
}