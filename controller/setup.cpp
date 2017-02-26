#include "setup.h"

auto setup::name() const -> std::string {
	return "setup";
}

auto setup::description() const -> std::string {
	return "Setup the game";
}

auto setup::run(context &ctx, controller::args_t const &args, ostream_t &out) const -> void {
	ctx.decks.create("infection"_h);
	ctx.decks.create("infection_discard"_h);
	ctx.decks.create("player"_h);
	ctx.decks.create("player_discard"_h);
	ctx.players.add_player("red"_h);
	ctx.players.set_role("red"_h, "dispatcher"_h);
	ctx.players.set_city("red"_h, "atlanta"_h);
	ctx.decks.create("red"_h);
	ctx.players.add_player("blue"_h);
	ctx.players.set_role("blue"_h, "scientist"_h);
	ctx.players.set_city("blue"_h, "atlanta"_h);
	ctx.decks.create("red"_h);
}