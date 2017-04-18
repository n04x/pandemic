#include "charter_flight_to.h"

auto charter_flight_to::name() const -> std::string {
	return "charter-flight-to";
}

auto charter_flight_to::description() const -> std::string {
	return "Take a chartered flight to a city";
}

auto charter_flight_to::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	auto discardDeck = "player_discard"_h;
	try {
		auto city = args.at(0);    // City to fly to
		if (args.size() > 1) {
			discardDeck = args.at(1);
		}
		auto player = ctx.players.get_current_turn();		// Get the information of which player is playing
		auto currentCity = ctx.players.get_city(player);    // City player is currently on
		auto role = ctx.players.get_role(player);			// Get the role of the player

		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
			if (*card == currentCity) {
				ctx.players.set_city(player, city);
				ctx.decks.remove(player, currentCity);
				ctx.decks.add_to_top(discardDeck, currentCity);
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
				out << "Chartered flight: " << player << " -> " << city << std::endl
					<< "Discarded " << currentCity << " from " << player << "'s hand!" << std::endl;
				return;
			}
		}

		out << player << " does not have " << currentCity << " card!" << std::endl;
		return;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <city> [discard_deck]" << std::endl;
	}


}
