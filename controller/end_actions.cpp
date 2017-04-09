#include "end_actions.h"

auto end_actions::name() const -> std::string {
	return "end-actions";
}

auto end_actions::description() const -> std::string {
	return "End your actions";
}

auto draw_cards(context &ctx, end_actions::args_type const &args, end_actions::ostream_type &out) -> void {
	auto player_hand = "player"_h;
	if (!args.empty()) {
		player_hand = args.at(0);
	}
	auto card_1 = ctx.decks.remove_from_top(player_hand);
	auto card_2 = ctx.decks.remove_from_top(player_hand);
	auto current_player = ctx.players.get_current_turn();
	ctx.decks.add_to_top(current_player, card_1);
	out << "'" << card_1 << "' added to your hand" << std::endl;
	ctx.decks.add_to_top(current_player, card_2);
	out << "'" << card_2 << "' added to your hand" << std::endl;
}

auto infect(context &ctx, end_actions::args_type const &args, end_actions::ostream_type &out) -> void {
	auto infection_deck = "infection"_h;
	auto discard_deck = "infection_discard"_h;
	if (!args.empty()) {
		infection_deck = args.at(0);
		discard_deck = args.at(1);
	}
	auto const infection_rate = ctx.game.get_infection_rate();
	for (int i = 0; i < infection_rate; i++) {
		auto const &city = ctx.decks.remove_from_top(infection_deck);
		ctx.decks.add_to_top(discard_deck, city);
		auto const &color = ctx.cities.get_color(city);
		// TODO handle eradicated diseases (not just cured)
		if (ctx.cities.get_cube_count(city, color) == 3) {
			out << "'" << city << "' caused an outbreak" << std::endl;
			// TODO handle outbreak
			break;
		}
		ctx.game.remove_cube_from_supply(color);
		ctx.cities.add_cube(city, color);
		out << "'" << city << "' was infected" << std::endl;
	}
}

auto end_actions::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	// TODO throw error if game not started
	draw_cards(ctx, args, out);
	infect(ctx, args, out);
	auto const &next = ctx.players.get_next_turn();
	ctx.players.start_turn(next);
}