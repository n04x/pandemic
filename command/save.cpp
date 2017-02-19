#include "save.h"
#include <fstream>

auto save::name() const -> std::string {
	return "save";
}

auto save::description() const -> std::string {
	return "Save map";
}

auto save::run(context &c, command::args_t const &args) const -> void {
	auto const &filename = args.at(0);
	std::ofstream s;
	s.open(filename);
	for (auto i : c.game_map) {
		auto city = i.first;
		auto color = c.game_map.get_color(city);
		s << color << " ";
		s << city << " ";
		for (auto connection = c.game_map.begin(city); connection != c.game_map.end(city); connection++) {
			s << *connection << " ";
		}
		s << std::endl;
	}
}