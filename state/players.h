#ifndef PANDEMIC_PLAYERS_H
#define PANDEMIC_PLAYERS_H

#include "../handle.h"
#include <unordered_map>

struct players {
	inline players(): p{} {
    }

	template<class OutputIt>
	auto get_players(OutputIt first) -> OutputIt {
		for (auto i : p) {
			*first++ = i.first;
		}
		return first;
	}

	inline auto add_player(handle color) -> void {
        p.emplace(color, player());
    }

	inline auto get_role(handle player) const -> handle {
        return p.at(player).role;
    }

	inline auto set_role(handle player, handle role) -> void {
        p.at(player).role = role;
    }

    inline auto get_city(handle player) const -> handle {
        return p.at(player).city;
    }

    inline auto set_city(handle player, handle city) -> void {
        p.at(player).city = city;
    }

private:
	struct player {
		handle role;
        handle city;
	};

	std::unordered_map<handle, player> p;
};

#endif //PANDEMIC_PLAYERS_H
