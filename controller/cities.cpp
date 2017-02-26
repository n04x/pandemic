#include "cities.h"
#include <iomanip>

auto cities::name() const -> std::string {
	return "cities";
}

auto cities::description() const -> std::string {
	return "Show cities";
}

auto cities::run(context &ctx, controller::args_t const &args, ostream_t &out) const -> void {
	static constexpr auto col1 = 14;
	static constexpr auto col2 = 8;
	static constexpr auto col3 = 14;
	static constexpr auto fill = ' ';
	out << std::left << std::setw(col1) << std::setfill(fill) << "CITY";
	out << std::left << std::setw(col2) << std::setfill(fill) << "COLOR";
	out << std::left << std::setw(col3) << std::setfill(fill) << "CONNECTIONS";
	out << std::endl;
	for (auto city : ctx.cities) {
		auto name = city.first;
		auto color = ctx.cities.get_color(name);
		out << std::left << std::setw(col1) << std::setfill(fill) << name;
		out << std::left << std::setw(col2) << std::setfill(fill) << color;
		for (auto connection = ctx.cities.begin(name); connection != ctx.cities.end(name); connection++) {
			out << *connection << " ";
		}
		out << std::endl;
	}
}