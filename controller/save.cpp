#include "save.h"
#include <fstream>

auto save::name() const -> std::string {
	return "save";
}

auto save::description() const -> std::string {
	return "Save map";
}

auto save::run(context &c, controller::args_t const &args) const -> void {
	auto const &filename = args.at(0);
	std::ofstream s;
	s.open(filename);
	for (auto i : c.cities) {
		auto city = i.first;
		auto color = c.cities.get_color(city);
		s << color << " ";
		s << city << " ";
		for (auto connection = c.cities.begin(city); connection != c.cities.end(city); connection++) {
			s << *connection << " ";
		}
		s << std::endl;
	}
}