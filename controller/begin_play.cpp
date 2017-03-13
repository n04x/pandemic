#include "begin_play.h"

auto begin_play::name() const -> std::string {
	return "begin-play";
}

auto begin_play::description() const -> std::string {
	return "Begin playing the game";
}

auto begin_play::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	auto const &it = ctx.players.begin();
	if (it == ctx.players.end()) {
		out << "begin-play: no players" << std::endl;
		return;
	}
	ctx.players.start_turn(it->first);
}