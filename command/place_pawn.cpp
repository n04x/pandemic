#include "place_pawn.h"

auto place_pawn::name() const -> std::string {
	return "place-pawn";
}

auto place_pawn::description() const -> std::string {
	return "Place player pawn";
}

auto place_pawn::run(context &c, command::args_t const &args) const -> void {
	auto const &player = args.at(0);
	auto const &city = args.at(1);
	// validate city
	try {
		c.game_map.get_color(city);
	} catch (std::out_of_range const &) {
		c.out << "'" << city << "' is not a valid city" << std::endl;
		return;
	}
	// move pawn or throw if invalid
	try {
		c.game_players.set_city(player, city);
	} catch (std::out_of_range const &) {
		c.out << "'" << player << "' is not a valid player" << std::endl;
	}
}
