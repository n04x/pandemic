#include <iomanip>
#include <iterator>
#include "status.h"

auto status::name() const -> std::string {
	return "status";
}

auto status::description() const -> std::string {
	return "Show game status";
}

auto status::run(context &c, command::args_t const &args) const -> void {
	static constexpr auto col1 = 8;
	static constexpr auto col2 = 12;
	static constexpr auto col3 = 12;
	static constexpr auto fill = ' ';
	c.out << std::left << std::setw(col1) << std::setfill(fill) << "PLAYER";
	c.out << std::left << std::setw(col2) << std::setfill(fill) << "ROLE";
	c.out << std::left << std::setw(col3) << std::setfill(fill) << "CITY";
	c.out << std::endl;
	for (auto i : c.game_players) {
		auto name = i.first;
		auto role = c.game_players.get_role(name);
		auto city = c.game_players.get_city(name);
		c.out << std::left << std::setw(col1) << std::setfill(fill) << name;
		c.out << std::left << std::setw(col2) << std::setfill(fill) << role;
		c.out << std::left << std::setw(col3) << std::setfill(fill) << city;
		c.out << std::endl;
	}
}