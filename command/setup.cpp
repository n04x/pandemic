#include "setup.h"

auto setup::name() const -> std::string {
	return "setup";
}

auto setup::description() const -> std::string {
	return "Setup the game";
}

auto setup::run(context &c, command::args_t const &args) const -> void {
	c.game_decks.create("infection"_h);
	c.game_decks.create("infection_discard"_h);
	c.game_decks.create("player"_h);
	c.game_decks.create("player_discard"_h);
	c.game_players.add_player("red"_h);
	c.game_players.set_role("red"_h, "dispatcher"_h);
	c.game_players.set_city("red"_h, "atlanta"_h);
	c.game_decks.create("red"_h);
	c.game_players.add_player("blue"_h);
	c.game_players.set_role("blue"_h, "scientist"_h);
	c.game_players.set_city("blue"_h, "atlanta"_h);
	c.game_decks.create("red"_h);
}