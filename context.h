#ifndef PANDEMIC_CONTEXT_H
#define PANDEMIC_CONTEXT_H

#include <ostream>
#include "state/players.h"
#include "state/decks.h"

struct context {
	inline context(std::ostream &out) : out{out}, p{}, d{} {}

	std::ostream &out;
	players p;
	decks d;
};

#endif //PANDEMIC_CONTEXT_H
