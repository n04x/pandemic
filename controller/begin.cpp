#include "begin.h"

auto begin::name() const -> std::string {
	return "begin";
}

auto begin::description() const -> std::string {
	return "Begin playing the game";
}

auto begin::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	auto const &it = ctx.players.begin();
	if (it == ctx.players.end()) {
		out << "begin: no players" << std::endl;
		return;
	}
	ctx.players.start_turn(it->first);
}