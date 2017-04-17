#include "players.h"
#include <iomanip>

auto players::name() const -> std::string {
	return "players";
}

auto players::description() const -> std::string {
	return "Show players";
}

auto players::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	static constexpr auto col1 = 7;
	static constexpr auto col2 = 22;
	static constexpr auto col3 = 12;
	static constexpr auto fill = ' ';
	out << std::left << std::setw(col1) << std::setfill(fill) << "PLAYER";
	out << std::left << std::setw(col2) << std::setfill(fill) << "ROLE";
	out << std::left << std::setw(col3) << std::setfill(fill) << "CITY";
	out << std::endl;
	for (auto player : ctx.players) {
		auto const &name = player.first;
		out << std::left << std::setw(col1) << std::setfill(fill) << name;
		out << std::left << std::setw(col2) << std::setfill(fill) << ctx.players.get_role(name);
		out << std::left << std::setw(col2) << std::setfill(fill) << ctx.players.get_city(name);
		out << std::endl;
	}
}