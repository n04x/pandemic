#ifndef PANDEMIC_CONTEXT_H
#define PANDEMIC_CONTEXT_H

#include <ostream>
#include "../state/players.h"

struct context {
	inline context(std::ostream &out) : out{out}, p{} {}

	std::ostream &out;
	players p;
};

#endif //PANDEMIC_CONTEXT_H
