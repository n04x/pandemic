#include "players.h"

players::players() : p() {
}

auto players::add_player(handle color) -> void {
	p.emplace(color, player());
}

auto players::get_role(handle player) const -> handle {
	return p.at(player).role;
}

auto players::set_role(handle player, handle role) -> void {
	p.at(player).role = role;
}
