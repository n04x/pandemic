#include "cities.h"
#include <iomanip>

auto cities::name() const -> std::string {
	return "cities";
}

auto cities::description() const -> std::string {
	return "Show cities";
}

auto cities::run(context &ctx, args_t const &args, ostream_t &out) const -> void {
	static constexpr auto col1 = 14;
	static constexpr auto col2 = 8;
	static constexpr auto colCube = 7;
	static constexpr auto col4 = 10;
	static constexpr auto col5 = 10;
	static constexpr auto fill = ' ';
	out << std::left << std::setw(col1) << std::setfill(fill) << "CITY";
	out << std::left << std::setw(col2) << std::setfill(fill) << "REGION";
	out << std::left << std::setw(colCube) << std::setfill(fill) << "BLACK";
	out << std::left << std::setw(colCube) << std::setfill(fill) << "YELLOW";
	out << std::left << std::setw(colCube) << std::setfill(fill) << "BLUE";
	out << std::left << std::setw(colCube) << std::setfill(fill) << "RED";
	out << std::left << std::setw(col4) << std::setfill(fill) << "RESEARCH";
	out << std::left << std::setw(col5) << std::setfill(fill) << "CONNECTIONS";
	out << std::endl;
	for (auto city : ctx.cities) {
		auto name = city.first;
		auto color = ctx.cities.get_color(name);
		out << std::left << std::setw(col1) << std::setfill(fill) << name;
		out << std::left << std::setw(col2) << std::setfill(fill) << color;
		out << std::left << std::setw(colCube) << std::setfill(fill) << ctx.cities.get_cube_count(name, "black"_h);
		out << std::left << std::setw(colCube) << std::setfill(fill) << ctx.cities.get_cube_count(name, "yellow"_h);
		out << std::left << std::setw(colCube) << std::setfill(fill) << ctx.cities.get_cube_count(name, "blue"_h);
		out << std::left << std::setw(colCube) << std::setfill(fill) << ctx.cities.get_cube_count(name, "red"_h);
		out << std::left << std::setw(col4) << std::setfill(fill) << ctx.cities.has_research_station(name);
		for (auto connection = ctx.cities.begin(name); connection != ctx.cities.end(name); connection++) {
			out << *connection << " ";
		}
		out << std::endl;
	}
}