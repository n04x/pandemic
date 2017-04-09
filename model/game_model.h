#ifndef PANDEMIC_GAME_MODEL_H
#define PANDEMIC_GAME_MODEL_H

#include <set>
#include <map>
#include "../handle.h"

// board represents the PANDEMIC game board.
struct game_model {
	inline auto cube_supply_count(handle color) const -> int {
		return cube_supply.at(color);
	}

	inline auto out_of_cubes() const -> bool {
		return cube_supply_count("black"_h) < 0 ||
			   cube_supply_count("yellow"_h) < 0 ||
			   cube_supply_count("blue"_h) < 0 ||
			   cube_supply_count("red"_h) < 0;
	}

	inline auto add_cube_to_supply(handle color, int amount = 1) -> void {
		cube_supply.at(color) += amount;
	}

	inline auto remove_cube_from_supply(handle color, int amount = 1) -> void {
		if (cube_supply_count(color) - amount < 0) {
			throw std::out_of_range{"out of cubes"};
		}
		cube_supply.at(color) -= amount;
	}

	inline auto discovered_cure(handle color) const -> bool {
		return discovered_cures.count(color) == 1;
	}

	inline auto all_cures_discovered() const -> bool {
		return discovered_cure("black"_h) &&
			   discovered_cure("yellow"_h) &&
			   discovered_cure("blue"_h) &&
			   discovered_cure("red"_h);
	}

	inline auto discover_cure(handle color) -> void {
		discovered_cures.insert(color);
	}

	inline auto get_outbreak_level() const -> int {
		return outbreak_level;
	}

	inline auto outbreak_limit_reached() -> bool {
		return get_outbreak_level() == outbreak_limit;
	}

	inline auto increase_outbreak_level() -> void {
		outbreak_level++;
	}

	inline auto get_infection_rate() const -> int {
		return infection_rate;
	}

	inline auto increase_infection_rate() -> void {
		infection_rate++;
	}

	inline auto research_station_supply_count() const -> int {
		return research_station_supply;
	}

	inline auto set_research_station_supply(int amount) -> void {
		research_station_supply = amount;
	}

	inline auto remove_research_station_supply() -> void {
		research_station_supply--;
	}

private:
	std::map<handle, int> cube_supply = {
			{"black"_h,  0},
			{"yellow"_h, 0},
			{"blue"_h,   0},
			{"red"_h,    0},
	};
	std::set<handle> discovered_cures;
	int const outbreak_limit = 8;
	int outbreak_level = 0;
	int infection_rate = 2;
	int research_station_supply;
};

#endif //PANDEMIC_GAME_MODEL_H
