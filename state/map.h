#ifndef PANDEMIC_MAP_H
#define PANDEMIC_MAP_H

#include "../handle.h"
#include <unordered_set>
#include <unordered_map>

// map represents a PANDEMIC map.
class map {
	using connected_cities_t = std::unordered_set<handle>;

	struct city {
		handle color;
		handle name;
		connected_cities_t connected_cities;
	};

	using cities_t = std::unordered_map<handle, city>;

	cities_t cities;

public:
	// TODO remove internal iterator leak
	using cities_const_iterator = cities_t::const_iterator;
	using connected_cities_const_iterator = connected_cities_t::const_iterator;

	inline auto add_city(handle color, handle name) -> void {
		cities.emplace(name, city{color, name});
	}

	inline auto connect_city(handle name, handle connection) -> void {
		cities.at(name).connected_cities.insert(connection);
	}

	inline auto get_color(handle name) const -> handle {
		return cities.at(name).color;
	}

	inline auto begin() const -> cities_const_iterator {
		return cities.begin();
	}

	inline auto end() const -> cities_const_iterator {
		return cities.end();
	}

	inline auto begin(handle city) const -> connected_cities_const_iterator {
		return cities.at(city).connected_cities.begin();
	}

	inline auto end(handle city) const -> connected_cities_const_iterator {
		return cities.at(city).connected_cities.end();
	}
};

#endif //PANDEMIC_MAP_H
