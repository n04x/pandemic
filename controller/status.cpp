#include <iomanip>
#include <iterator>
#include "status.h"

auto status::name() const -> std::string {
	return "status";
}

auto status::description() const -> std::string {
	return "Show game status";
}

auto status::run(context &ctx, controller::args_t const &args, ostream_t &out) const -> void {
	static constexpr auto col1 = 8;
	static constexpr auto col2 = 12;
	static constexpr auto col3 = 12;
	static constexpr auto fill = ' ';
	out << std::left << std::setw(col1) << std::setfill(fill) << "PLAYER";
	out << std::left << std::setw(col2) << std::setfill(fill) << "ROLE";
	out << std::left << std::setw(col3) << std::setfill(fill) << "CITY";
	out << std::endl;
	for (auto i : ctx.players) {
		auto name = i.first;
		auto role = ctx.players.get_role(name);
		auto city = ctx.players.get_city(name);
		out << std::left << std::setw(col1) << std::setfill(fill) << name;
		out << std::left << std::setw(col2) << std::setfill(fill) << role;
		out << std::left << std::setw(col3) << std::setfill(fill) << city;
		out << std::endl;
	}
}