#include "place_pawn.h"

auto place_pawn::name() const -> std::string {
	return "place-pawn";
}

auto place_pawn::description() const -> std::string {
	return "Place player pawn";
}

auto place_pawn::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	try {
		auto const &player = args.at(0);
		auto const &city = args.at(1);
		// validate city
		try {
			ctx.cities.get_color(city);
		} catch (std::out_of_range const &) {
			out << "'" << city << "' is not a valid city" << std::endl;
			return;
		}
		// move pawn or throw if invalid
		try {
			ctx.players.set_city(player, city);
		} catch (std::out_of_range const &) {
			out << "'" << player << "' is not a valid player" << std::endl;
		}
	} catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player> <city>" << std::endl;
	}
}
