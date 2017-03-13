#include "validate_city_connections.h"
#include <algorithm>

auto validate_city_connections::name() const -> std::string {
	return "validate-city-connections";
}

auto validate_city_connections::description() const -> std::string {
	return "Print any city connection validation errors";
}

auto validate_city_connections::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	for (auto const &i : ctx.cities) {
		auto const &city = i.first;
		for (auto j = ctx.cities.begin(city); j != ctx.cities.end(city); j++) {
			auto const &connection = *j;
			try {
				auto const &found = std::find(ctx.cities.begin(connection), ctx.cities.end(connection), city);
				if (found == ctx.cities.end(connection)) {
					out << name() << ": '" << connection << "' missing connection to '" << city << "'" << std::endl;
				}
			} catch (std::out_of_range const &) {
				out << name() << ": '" << city << "' connected to unknown city '" << connection << "'" << std::endl;
			}
		}
	}
}