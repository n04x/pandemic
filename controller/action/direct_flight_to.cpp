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
		if (args.size() > 1) {
			discard_deck = args.at(1);
		}
		auto player = ctx.players.get_current_turn();    // Get the information of which player is playing
		ctx.decks.remove(player, city);
		ctx.decks.add_to_top(discard_deck, city);                // Add the card to the discard card deck
		ctx.players.set_city(player, city);                // Set the new position of player
		ctx.players.decrement_actions_remaining();
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<city> [discard_deck]" << std::endl;
	}
}