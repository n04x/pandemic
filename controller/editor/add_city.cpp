#include "add_city.h"
#include <iterator>

auto add_city::name() const -> std::string {
	return "add-city";
}

auto add_city::description() const -> std::string {
	return "region name connection ...";
}

auto add_city::run(context &ctx, controller::args_t const &args) const -> void {
	auto region = args.at(0);
	auto name = args.at(1);
	ctx.cities.add_city(region, name);
	for (auto connection = std::next(args.begin(), 2); connection != args.end(); connection++) {
		ctx.cities.connect_city(name, *connection);
	}
}