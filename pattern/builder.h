#ifndef PANDEMIC_BUILDER_H
#define PANDEMIC_BUILDER_H

#include <utility>
#include <vector>
#include "../handle.h"

struct city_product {
	friend struct city_builder;

	handle name;
	handle region;
	std::vector<handle> connections;

private:
	inline city_product() {};
};

struct city_builder {
	inline auto get_city() const -> city_product const {
		return city;
	}

	inline auto build_name(handle name) -> void {
		city.name = name;
	}

	inline auto build_region(handle region) -> void {
		city.region = region;
	}

	inline auto build_connection(handle connection) -> void {
		city.connections.push_back(connection);
	}

private:
	city_product city;
};

#endif //PANDEMIC_BUILDER_H
