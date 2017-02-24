#ifndef PANDEMIC_CONTEXT_H
#define PANDEMIC_CONTEXT_H

#include <ostream>
#include "model/players_model.h"
#include "model/decks_model.h"
#include "model/cities_model.h"
#include "model/game_model.h"

// context represents the game state.
struct context {
	inline context(std::ostream &out) : out{out}, players{}, decks{}, cities{}, game{} {}

	// out prints text to the user.
	std::ostream &out;

	// players represents all the game players.
	players_model players;

	// decks represents all the game decks.
	decks_model decks;

	// cities represents the PANDEMIC map.
	cities_model cities;

	// game represents the PANDEMIC game.
	game_model game;
};

#endif //PANDEMIC_CONTEXT_H
