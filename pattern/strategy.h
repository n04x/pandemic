#ifndef PANDEMIC_STRATEGY_H
#define PANDEMIC_STRATEGY_H

#include "../model/decks_model.h"

struct strategy {
	virtual auto execute(decks_model &decks, handle deck) -> handle = 0;
};

struct draw_card_from_top : strategy {
	virtual auto execute(decks_model &decks, handle deck) -> handle {
		return decks.remove_from_top(deck);
	}
};

struct draw_card_from_bottom : strategy {
	virtual auto execute(decks_model &decks, handle deck) -> handle {
		return decks.remove_from_bottom(deck);
	}
};

struct draw_card {
	inline draw_card(strategy *s) : s{s} {}

	inline auto set_strategy(strategy *s) -> void {
		this->s = s;
	}

	inline auto execute_strategy(decks_model &decks, handle deck) -> handle {
		return s->execute(decks, deck);
	}

private:
	strategy *s;
};

#endif //PANDEMIC_STRATEGY_H
