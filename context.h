#ifndef PANDEMIC_CONTEXT_H
#define PANDEMIC_CONTEXT_H

#include <ostream>
#include "state/players.h"
#include "state/decks.h"
#include "state/map.h"

// context represents the game state.
struct context {
	inline context(std::ostream &out) : out{out}, game_players{}, game_decks{} {}

	// out prints text to the user.
	std::ostream &out;

	// game_players represents all the game players.
	players game_players;

	// game_decks represents all the game decks.
	decks game_decks;

	// game_map represents the PANDEMIC map.
	map game_map;
};

#endif //PANDEMIC_CONTEXT_H
