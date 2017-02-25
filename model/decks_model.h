#ifndef PANDEMIC_DECKS_MODEL_H
#define PANDEMIC_DECKS_MODEL_H

#include <unordered_map>
#include <deque>
#include <algorithm>
#include <random>
#include "../handle.h"

// decks represents a collection of card decks.
struct decks_model {
    using cards_t = std::deque<handle>;
    using const_iterator = cards_t::const_iterator;

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
        std::remove(cards.begin(), cards.end(), card);
    }

    inline auto begin(handle name) const -> const_iterator {
        return decks.at(name).cards.begin();
    }

    inline auto end(handle name) const -> const_iterator {
        return decks.at(name).cards.end();
    }

    inline auto size(handle name) const -> cards_t::size_type {
        return decks.at(name).cards.size();
    }

    inline auto shuffle(handle name) -> void {
        static std::random_device rd;
        static std::mt19937 g{rd()};
        auto &cards = decks.at(name).cards;
        std::shuffle(cards.begin(), cards.end(), g);
    }

private:
    struct deck {
        cards_t cards;
    };

    std::unordered_map<handle, deck> decks;
};

#endif //PANDEMIC_DECKS_MODEL_H
