#ifndef PANDEMIC_DIRECTOR_H
#define PANDEMIC_DIRECTOR_H

#include "builder.h"

struct city_director {
	inline auto set_city_builder(city_builder * builder) -> void {
		this->builder = builder;
	}

	inline auto get_city() const -> city_product const {
		return builder->get_city();
	}

	inline auto construct_city(handle name, handle region, std::vector<handle> connections) -> void {
		builder->build_name(name);
		builder->build_region(region);
		for (auto c : connections) {
			builder->build_connection(c);
		}
	}

private:
	city_builder * builder;
};

#endif //PANDEMIC_DIRECTOR_H
