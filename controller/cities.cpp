#include "cities.h"
#include <iomanip>

auto cities::name() const -> std::string {
	return "cities";
}

auto cities::description() const -> std::string {
	return "Show cities";
}

auto cities::run(context &c, controller::args_t const &args) const -> void {
	static constexpr auto col1 = 14;
	static constexpr auto col2 = 8;
	static constexpr auto col3 = 14;
	static constexpr auto fill = ' ';
	c.out << std::left << std::setw(col1) << std::setfill(fill) << "CITY";
	c.out << std::left << std::setw(col2) << std::setfill(fill) << "COLOR";
	c.out << std::left << std::setw(col3) << std::setfill(fill) << "CONNECTIONS";
	c.out << std::endl;
	for (auto city : c.cities) {
		auto name = city.first;
		auto color = c.cities.get_color(name);
		c.out << std::left << std::setw(col1) << std::setfill(fill) << name;
		c.out << std::left << std::setw(col2) << std::setfill(fill) << color;
		for (auto connection = c.cities.begin(name); connection != c.cities.end(name); connection++) {
			c.out << *connection << " ";
		}
		c.out << std::endl;
	}
}