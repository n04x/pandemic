#ifndef PANDEMIC_PLAYERS_H
#define PANDEMIC_PLAYERS_H

#include "../handle.h"
#include <unordered_map>

struct players {
	players();

	template<class OutputIt>
	auto get_players(OutputIt first) -> OutputIt {
		for (auto i : p) {
			*first++ = i.first;
		}
		return first;
	}

	auto add_player(handle player) -> void;

	auto get_role(handle player) const -> handle;

	auto set_role(handle player, handle role) -> void;

private:
	struct player {
		handle role;
	};

	std::unordered_map<handle, player> p;
};

#endif //PANDEMIC_PLAYERS_H
