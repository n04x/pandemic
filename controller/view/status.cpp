#include <iomanip>
#include <iterator>
#include "status.h"

auto status::name() const -> std::string {
	return "status";
}

auto status::description() const -> std::string {
	return "Show game status";
}

auto status::run(context &ctx, args_t const &args, ostream_t &out) const -> void {
	auto const &turn = ctx.players.get_current_turn();
	if (turn == ""_h) {
		out << "status: game not started" << std::endl;
		return;
	}
	static constexpr auto col1 = 5;
	static constexpr auto col2 = 8;
	static constexpr auto fill = ' ';
	out << std::left << std::setw(col1) << std::setfill(fill) << "TURN";
	out << std::left << std::setw(col2) << std::setfill(fill) << "REMAINING";
	out << std::endl;
	out << std::left << std::setw(col1) << std::setfill(fill) << ctx.players.get_current_turn();
	out << std::left << std::setw(col2) << std::setfill(fill) << ctx.players.get_actions_remaining();
	out << std::endl;
}