#include "give_role.h"
#include <vector>


auto give_role::name() const -> std::string {
	return "give-role";
}

auto give_role::description() const -> std::string {
	return "Give random role to player";
}

auto give_role::run(context &ctx, args_type const &args, ostream_type &out) const -> void
{
	auto player_name = args.at(0);
	auto player_role = args.at(1);
	ctx.players.set_role(player_name, player_role);

	//Create extra deck of 1 card for Contingency Planner
	if (player_role == "contingency_planner"_h) {
		ctx.decks.create("contingency_planner"_h);
	}
}
