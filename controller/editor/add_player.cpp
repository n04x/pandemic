#include "add_player.h"

auto add_player::name() const -> std::string {
	return "add-player";
}

auto add_player::description() const -> std::string {
	return "Add a player to the game";
}

auto add_player::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto name = args.at(0);
		ctx.players.add_player(name);
	} catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player>" << std::endl;
	}
}