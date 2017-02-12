#include <vector>
#include <iomanip>
#include <iterator>
#include "status.h"

auto status::name() const -> std::string {
	return "status";
}

auto status::description() const -> std::string {
	return "Show game status";
}

auto status::run(context &c) const -> void {
	std::vector<handle> v;
	c.p.get_players(std::back_inserter(v));
	if (v.empty()) {
		c.out << "no players" << std::endl;
		return;
	}
	static constexpr auto col1 = 8;
	static constexpr auto col2 = 10;
	static constexpr auto fill = ' ';
	c.out << std::left << std::setw(col1) << std::setfill(fill) << "PLAYER";
	c.out << std::left << std::setw(col2) << std::setfill(fill) << "ROLE";
	c.out << std::endl;
	for (auto i : v) {
		auto role = c.p.get_role(i);
		c.out << std::left << std::setw(col1) << std::setfill(fill) << i;
		c.out << std::left << std::setw(col2) << std::setfill(fill) << role;
		c.out << std::endl;
	}
}