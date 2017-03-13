#include "add_city.h"
#include <iterator>

auto add_city::name() const -> std::string {
	return "add-city";
}

auto add_city::description() const -> std::string {
	return "Add a city to the map";
}

auto add_city::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto region = args.at(0);
		auto name = args.at(1);
		ctx.cities.add_city(region, name);
		for (auto connection = std::next(args.begin(), 2); connection != args.end(); connection++) {
			ctx.cities.connect_city(name, *connection);
		}
	} catch (std::out_of_range const &) {
		out << "usage: " << name() << " <region> <name> <connection>..." << std::endl;
	}
}