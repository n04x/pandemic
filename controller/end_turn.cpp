#include "end_turn.h"

auto end_turn::name() const -> std::string {
	return "end-turn";
}

auto end_turn::description() const -> std::string {
	return "End your turn";
}

auto end_turn::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	// TODO throw error if game not started
	auto const &next = ctx.players.get_next_turn();
	ctx.players.start_turn(next);
}