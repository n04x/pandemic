#include "save.h"
#include <fstream>

auto save::name() const -> std::string {
	return "save";
}

auto save::description() const -> std::string {
	return "Save map";
}

auto save::run(context &ctx, controller::args_t const &args, ostream_t &out) const -> void {
	auto const &filename = args.at(0);
	std::ofstream s;
	s.open(filename);
	for (auto i : ctx.cities) {
		auto city = i.first;
		auto color = ctx.cities.get_color(city);
		s << color << " ";
		s << city << " ";
		for (auto connection = ctx.cities.begin(city); connection != ctx.cities.end(city); connection++) {
			s << *connection << " ";
		}
		s << std::endl;
	}
}