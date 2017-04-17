#ifndef PANDEMIC_PLAYERS_MODEL_H
#define PANDEMIC_PLAYERS_MODEL_H

#include "../handle.h"
#include <map>
#include <vector>
#include <algorithm>

class players_model {
	struct player {
		handle role;
		handle city;
	};

	using players_type = std::map<handle, player>;

	players_type players;
	std::vector<handle> turn_order;
	handle current_turn;
	int actions_remaining;
	bool skipping_next_infection_phase;

public:
	using const_iterator = players_type::const_iterator;

	static const int actions_per_turn = 4;

	inline auto begin() const -> const_iterator {
		return players.begin();
	}

	inline auto end() const -> const_iterator {
		return players.end();
	}

	inline auto add_player(handle color) -> void {
		players.emplace(color, player{color});
		turn_order.push_back(color);
	}

	inline auto get_role(handle player) const -> handle {
		return players.at(player).role;
	}

	inline auto set_role(handle player, handle role) -> void {
		players.at(player).role = role;
	}

	inline auto get_city(handle player) const -> handle {
		return players.at(player).city;
	}

	inline auto set_city(handle player, handle city) -> void {
		players.at(player).city = city;
	}

	inline auto get_actions_remaining() const -> int {
		return actions_remaining;
	}

	inline auto decrement_actions_remaining() -> void {
		actions_remaining--;
	}

	inline auto get_current_turn() const -> handle {
		return current_turn;
	}

	inline auto get_next_turn() const -> handle {
		auto it = std::find(turn_order.begin(), turn_order.end(), current_turn);
		it++;
		if (it == turn_order.end()) {
			return *turn_order.begin();
		}
		return *it;
	}

	inline auto start_turn(handle player) -> void {
		current_turn = player;
		actions_remaining = actions_per_turn;
		skipping_next_infection_phase = false;
	}


	inline auto skip_next_infection_phase() -> void {
		skipping_next_infection_phase = true;
	}

	inline auto is_skipping_next_infection_phase() -> bool {
		return skipping_next_infection_phase;
	}
};

#endif //PANDEMIC_PLAYERS_MODEL_H
