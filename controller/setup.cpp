#include "setup.h"

auto setup::name() const -> std::string {
	return "setup";
}

auto setup::description() const -> std::string {
	return "Setup the game";
}

auto setup::run(context &c, controller::args_t const &args) const -> void {
	c.decks.create("infection"_h);
	c.decks.create("infection_discard"_h);
	c.decks.create("player"_h);
	c.decks.create("player_discard"_h);
	c.players.add_player("red"_h);
	c.players.set_role("red"_h, "dispatcher"_h);
	c.players.set_city("red"_h, "atlanta"_h);
	c.decks.create("red"_h);
	c.players.add_player("blue"_h);
	c.players.set_role("blue"_h, "scientist"_h);
	c.players.set_city("blue"_h, "atlanta"_h);
	c.decks.create("red"_h);
}