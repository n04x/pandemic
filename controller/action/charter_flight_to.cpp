#include "charter_flight_to.h"

auto charter_flight_to::name() const -> std::string
{
	return "charter_flight_to";
}

auto charter_flight_to::description() const -> std::string
{
	return "Take a chartered flight to a city";
}

auto charter_flight_to::run(context & ctx, args_t const & args, ostream_t & out) const -> void
{
	try {
		auto city = args.at(0);
		auto player = ctx.players.get_current_turn();	// Get the information of which player is playing
		auto currentCity = ctx.players.get_city(player);	// City player is currently on

		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {
			if (*card == city) {
				ctx.players.set_city(player, city);
				ctx.decks.remove(player, city);
				ctx.decks.add_to_top(args.at(1), city);
				return;
			}
		}

		out << "Player does not have city card!" << std::endl;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <city>" << std::endl;
	}


}