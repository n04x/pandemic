#ifndef PANDEMIC_DECKS_MODEL_H
#define PANDEMIC_DECKS_MODEL_H

#include <unordered_map>
#include <deque>
#include <algorithm>
#include <random>
#include "../handle.h"

// decks represents a collection of card decks.

class decks_model {
	using cards_t = std::deque<handle>;

	struct deck {
		cards_t cards;
	};

	using decks_t = std::unordered_map<handle, deck>;

	decks_t decks;

public:
	using const_iterator = decks_t::const_iterator;
	using cards_const_iterator = cards_t::const_iterator;

	inline auto create(handle name) -> void {
		decks.emplace(name, deck{});
	}

	inline auto add_to_top(handle name, handle card) -> void {
		decks.at(name).cards.push_front(card);
	}

	inline auto remove_from_top(handle name) -> handle {
		auto &cards = decks.at(name).cards;
		auto result = cards.front();
		cards.pop_front();
		return result;
	}

	inline auto remove_from_bottom(handle name) -> handle {
		auto &cards = decks.at(name).cards;
		auto result = cards.back();
		cards.pop_back();
		return result;
	}

	inline auto remove(handle name, handle card) -> void {
		auto &cards = decks.at(name).cards;
		cards.erase(std::remove(cards.begin(), cards.end(), card), cards.end());
	}

	inline auto begin() const -> const_iterator {
		return decks.begin();
	}

	inline auto end() const -> const_iterator {
		return decks.end();
	}

	inline auto begin(handle name) const -> cards_const_iterator {
		return decks.at(name).cards.begin();
	}

	inline auto end(handle name) const -> cards_const_iterator {
		return decks.at(name).cards.end();
	}

	inline auto size(handle name) const -> cards_t::size_type {
		return decks.at(name).cards.size();
	}

	inline auto shuffle(handle name) -> void {
		static std::minstd_rand g{};
		auto &cards = decks.at(name).cards;
		std::shuffle(cards.begin(), cards.end(), g);
	}
};

#endif //PANDEMIC_DECKS_MODEL_H
