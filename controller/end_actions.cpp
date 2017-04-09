#include "end_actions.h"
#include <algorithm>
#include <vector>

auto end_actions::name() const -> std::string {
	return "end";
}

auto end_actions::description() const -> std::string {
	return "End your actions";
}

static auto cube_limit = 3;

auto outbreak(context &ctx, end_actions::ostream_type &out, handle target, handle color, std::vector<handle> &infected) -> void {
	ctx.game.increase_outbreak_level();
	out << "outbreak level increased to '" << ctx.game.get_outbreak_level() << "'" << std::endl;

	for (auto i = ctx.cities.begin(target); i != ctx.cities.end(target); i++) {
		auto city = *i;

		// Ignore connected cities that have not been defined.
		if (!ctx.cities.exists(city)) {
			continue;
		}
		// Do not infect cities that already had an outbreak
		if (std::find(infected.begin(), infected.end(), city) != infected.end()) {
			continue;
		}
		infected.push_back(city);

		if (ctx.cities.get_cube_count(city, color) == cube_limit) {
			outbreak(ctx, out, city, color, infected);
			continue;
		}
		ctx.game.remove_cube_from_supply(color);
		ctx.cities.add_cube(city, color);
		out << "'" << city << "' was infected due to an outbreak from '" << target << "'" << std::endl;
	}
}

auto epidemic(context &ctx, end_actions::args_type const &args, end_actions::ostream_type &out) -> void {
	// (1) Increase
	ctx.game.increase_infection_rate();
	out << "infection rate increased to '" << ctx.game.get_infection_rate() << "'" << std::endl;

	// (2) Infect
	auto city = ctx.decks.remove_from_bottom("infection"_h);
	ctx.decks.add_to_top("infection_discard"_h, city);
	auto color = ctx.cities.get_color(city);
	if (!ctx.cities.eradicated_disease(color)) {
		auto cube_count = ctx.cities.get_cube_count(city, color);
		if (cube_count != 0) {
			auto amount = cube_limit - cube_count;
			ctx.game.remove_cube_from_supply(color, amount);
			ctx.cities.add_cube(city, color, amount);
			std::vector<handle> infected;
			outbreak(ctx, out, city, color, infected);
		} else {
			ctx.game.remove_cube_from_supply(color, cube_limit);
			ctx.cities.add_cube(city, color, cube_limit);
			out << "'" << city << "' was infected from an epidemic card" << std::endl;
		}
	}

	// (3) Intensify
	ctx.decks.shuffle("infection_discard"_h);
	for (auto i = ctx.decks.begin("infection_discard"_h); i != ctx.decks.end("infection_discard"_h); i++) {
		ctx.decks.add_to_top("infection"_h, *i);
	}
}

auto draw_card(context &ctx, end_actions::args_type const &args, end_actions::ostream_type &out) -> void {
	static const std::array<handle, 6> epidemic_cards = {"epidemic_1"_h, "epidemic_2"_h, "epidemic_3"_h, "epidemic_4"_h, "epidemic_5"_h, "epidemic_6"_h};
	auto player_deck = "player"_h;
	if (!args.empty()) {
		player_deck = args.at(0);
	}
	auto current_player = ctx.players.get_current_turn();
	auto card = ctx.decks.remove_from_top(player_deck);
	if (std::find(epidemic_cards.begin(), epidemic_cards.end(), card) != epidemic_cards.end()) {
		out << "epidemic card was drawn" << std::endl;
		epidemic(ctx, args, out);
	} else {
		ctx.decks.add_to_top(current_player, card);
		out << "'" << card << "' added to your hand" << std::endl;
	}
}

auto draw_cards(context &ctx, end_actions::args_type const &args, end_actions::ostream_type &out) -> void {
	draw_card(ctx, args, out);
	draw_card(ctx, args, out);
}

auto hand_limit(context &ctx, end_actions::args_type const &args, end_actions::ostream_type &out) -> void {
	static const auto limit = 7;
	auto current_player = ctx.players.get_current_turn();
	if (ctx.decks.size(current_player) > limit) {
		auto card = ctx.decks.remove_from_bottom(current_player);
		ctx.decks.add_to_top("player_discard"_h, card);
		out << "'" << current_player << "' player reached hand limit, discarding '" << card << "'" << std::endl;
	}
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
		if (ctx.cities.eradicated_disease(color)) {
			continue;
		}
		if (ctx.cities.get_cube_count(city, color) == 3) {
			out << "'" << city << "' had an outbreak from an infection card" << std::endl;
			std::vector<handle> infected;
			outbreak(ctx, out, city, color, infected);
			continue;
		}
		ctx.game.remove_cube_from_supply(color);
		ctx.cities.add_cube(city, color);
		out << "'" << city << "' was infected from an infection card" << std::endl;
	}
}

auto end_actions::run(context &ctx, args_type const &args, ostream_type &out) const -> void {
	// TODO throw error if game not started
	draw_cards(ctx, args, out);
	hand_limit(ctx, args, out);
	infect(ctx, args, out);
	auto const &next = ctx.players.get_next_turn();
	ctx.players.start_turn(next);
}