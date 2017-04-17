#include "store_event.h"

auto store_event::name() const -> std::string
{
	return "store-event";
}

auto store_event::description() const -> std::string
{
	return "Take discarded event card and store it seperate from hand (Contingency Planner only)";
}

auto store_event::run(context & ctx, args_type const & args, ostream_type & out) const -> void
{
	try {

		auto event = args.at(0);	//event to store
		auto player = ctx.players.get_current_turn();    // Get the information of which player is playing
		auto playerDiscard = "player_discard"_h;


		if (ctx.players.get_role(player) != "contingency_planner"_h) {
			out << "You are not a Contingency Planner!" << std::endl;
			return;
		}

		if (ctx.decks.size("contingency_planner"_h) == 0) {
			for (auto card = ctx.decks.begin(playerDiscard); card != ctx.decks.end(playerDiscard); card++) {
				if (*card == event) {
					ctx.decks.remove(playerDiscard, event);
					ctx.decks.add_to_top("contingency_planner"_h, event);
					ctx.players.decrement_actions_remaining();

					out << "Placed " << event << " on top of contingency planner role card!" << std::endl;
					
					return;
				}
			}
		}

		out << event << " not found in " << playerDiscard << "!" << std::endl;
		return;
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <event>" << std::endl;
	}

}
