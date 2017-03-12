#include "direct_flight_to.h"

auto direct_flight_to::name() const->std::string {
	return "direct-flight-to...";
}

auto direct_flight_to::description() const->std::string {
	return "Direct Flight To ...";
}

auto direct_flight_to::run(context &ctx, args_t const &args, ostream_t &out) const-> void {
	try	{
		auto city = args.at(0);
		auto deck = args.at(1);
		auto player = ctx.players.get_current_turn();	// Get the information of which player is playing
		ctx.decks.add_to_top(deck, city);				// Add the card to the discard card deck
		ctx.players.set_city(player, city);				// Set the new position of player
		ctx.players.decrement_actions_remaining();
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<city> <discard_deck>" << std::endl;
	}
}