#ifndef PANDEMIC_DECORATOR_H
#define PANDEMIC_DECORATOR_H

#include "../model/decks_model.h"
#include <algorithm>
#include <iterator>

struct decks_decorator : decks_model {
	inline decks_decorator(decks_model const &decks) : decks_model{decks} {
	}

	inline virtual auto get_cards() const -> std::vector<handle> {
		std::vector<handle> result;
		for (auto card : *this) {
			result.push_back(card.first);
		}
		return result;
	}
};

struct epidemic_decks_decorator : decks_decorator {
	inline epidemic_decks_decorator(decks_model const &decks) : decks_decorator{decks} {
	}

	inline auto get_cards() const -> std::vector<handle> override {
		static std::vector<handle> epidemic_cards = {"epidemic_1"_h, "epidemic_2"_h, "epidemic_3"_h, "epidemic_4"_h, "epidemic_5"_h, "epidemic_6"_h};
		auto cards = decks_decorator::get_cards();
		std::sort(epidemic_cards.begin(), epidemic_cards.end());
		std::sort(cards.begin(), cards.end());
		std::vector<handle> result;
		std::set_intersection(epidemic_cards.begin(), epidemic_cards.end(), cards.begin(), cards.end(), std::back_inserter(result));
		return result;
	}
};

struct event_decks_decorator : decks_decorator {
	inline event_decks_decorator(decks_model const &decks) : decks_decorator{decks} {
	}

	inline auto get_cards() const -> std::vector<handle> override {
		static std::vector<handle> role_cards = {"one_quiet_night"_h, "forecast"_h, "government_grant"_h, "resilient_population"_h, "airlift"_h};
		auto cards = decks_decorator::get_cards();
		std::sort(role_cards.begin(), role_cards.end());
		std::sort(cards.begin(), cards.end());
		std::vector<handle> result;
		std::set_intersection(role_cards.begin(), role_cards.end(), cards.begin(), cards.end(), std::back_inserter(result));
		return result;
	}
};

#endif //PANDEMIC_DECORATOR_H
