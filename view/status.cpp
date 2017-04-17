#include <iomanip>
#include <iterator>
#include "status.h"

auto status::name() const -> std::string {
	return "status";
}

auto status::description() const -> std::string {
	return "Show game status";
}

auto status::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	auto const &turn = ctx.players.get_current_turn();
	if (turn == ""_h) {
		out << "status: game not started" << std::endl;
		return;
	}
	static constexpr auto col1 = 7;
	static constexpr auto col2 = 8;
	static constexpr auto col3 = 12;
	static constexpr auto fill = ' ';
	out << std::left << std::setw(col1) << std::setfill(fill) << "TURN";
	out << std::left << std::setw(col2) << std::setfill(fill) << "ACTIONS";
	out << std::left << std::setw(col2) << std::setfill(fill) << "BLACK";
	out << std::left << std::setw(col2) << std::setfill(fill) << "YELLOW";
	out << std::left << std::setw(col2) << std::setfill(fill) << "BLUE";
	out << std::left << std::setw(col2) << std::setfill(fill) << "RED";
	out << std::left << std::setw(col3) << std::setfill(fill) << "RESEARCH";
	out << std::left << std::setw(col3) << std::setfill(fill) << "OUTBREAK";
	out << std::left << std::setw(col3) << std::setfill(fill) << "INFECTION";
	out << std::left << std::setw(col2) << std::setfill(fill) << "CURES";
	out << std::endl;
	out << std::left << std::setw(col1) << std::setfill(fill) << ctx.players.get_current_turn();
	out << std::left << std::setw(col2) << std::setfill(fill) << ctx.players.get_actions_remaining();
	out << std::left << std::setw(col2) << std::setfill(fill) << ctx.game.cube_supply_count("black"_h);
	out << std::left << std::setw(col2) << std::setfill(fill) << ctx.game.cube_supply_count("yellow"_h);
	out << std::left << std::setw(col2) << std::setfill(fill) << ctx.game.cube_supply_count("blue"_h);
	out << std::left << std::setw(col2) << std::setfill(fill) << ctx.game.cube_supply_count("red"_h);
	out << std::left << std::setw(col3) << std::setfill(fill) << ctx.game.research_station_supply_count();
	out << std::left << std::setw(col3) << std::setfill(fill) << ctx.game.get_outbreak_level();
	out << std::left << std::setw(col3) << std::setfill(fill) << ctx.game.get_infection_rate();
	bool discovered_cure{false};
	if (ctx.game.discovered_cure("black"_h)) {
		out << "black ";
		discovered_cure = true;
	}
	if (ctx.game.discovered_cure("yellow"_h)) {
		out << "yellow ";
		discovered_cure = true;
	}
	if (ctx.game.discovered_cure("red"_h)) {
		out << "red ";
		discovered_cure = true;
	}
	if (ctx.game.discovered_cure("blue"_h)) {
		out << "blue ";
		discovered_cure = true;
	}
	if (!discovered_cure) {
		out << "(none)";
	}
	out << std::endl;
}