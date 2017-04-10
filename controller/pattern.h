#ifndef PANDEMIC_PATTERN_H
#define PANDEMIC_PATTERN_H

#include <iostream>
#include <iomanip>
#include <memory>
#include "../command.h"
#include "../pattern/subject.h"
#include "../pattern/director.h"
#include "../pattern/decorator.h"
#include "../pattern/strategy.h"

struct observable_cities_model : subject {
	inline observable_cities_model(cities_model &model): model{model} {}

	inline auto add_city(handle color, handle name) -> void {
		model.add_city(color, name);
		notify();
	}

	inline auto connect_city(handle name, handle connection) -> void {
		model.connect_city(name, connection);
		notify();
	}

	inline auto place_research_station(handle name) -> void {
		model.place_research_station(name);
		notify();
	}

	inline auto remove_research_station(handle name) -> void {
		model.remove_research_station(name);
		notify();
	}

	inline auto add_cube(handle name, handle color, int count = 1) -> void {
		model.add_cube(name, color, count);
		notify();
	}

	inline auto remove_cube(handle name, handle color, int count = 1) -> void {
		model.remove_cube(name, color, count);
		notify();
	}

private:
	cities_model &model;
};

class map_view : public observer {
	context &ctx;

public:
	inline explicit map_view(context &ctx) : ctx{ctx} {
	}

	virtual inline auto update() -> void override {
		auto &out = std::cout;
		static constexpr auto col1 = 14;
		static constexpr auto col2 = 8;
		static constexpr auto col5 = 10;
		static constexpr auto fill = ' ';
		out << std::left << std::setw(col1) << std::setfill(fill) << "CITY";
		out << std::left << std::setw(col2) << std::setfill(fill) << "REGION";
		out << std::left << std::setw(col5) << std::setfill(fill) << "CONNECTIONS";
		out << std::endl;
		for (auto city : ctx.cities) {
			auto name = city.first;
			auto color = ctx.cities.get_color(name);
			out << std::left << std::setw(col1) << std::setfill(fill) << name;
			out << std::left << std::setw(col2) << std::setfill(fill) << color;
			for (auto connection = ctx.cities.begin(name); connection != ctx.cities.end(name); connection++) {
				out << *connection << " ";
			}
			out << std::endl;
		}
	}
};

struct pattern_driver : command {
	virtual inline auto name() const -> std::string override {
		return "pattern";
	}

	virtual inline auto description() const -> std::string override {
		return "Demonstrates the design patterns";
	}

	virtual inline auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override {

		// Demonstrate observers
		observable_cities_model subject{ctx.cities};
		map_view view{ctx};
		subject.attach(&view);
		subject.add_city("blue"_h, "a_city"_h);
		out << std::endl;
		subject.connect_city("a_city"_h, "montreal"_h);
		out << std::endl;
		subject.connect_city("montreal"_h, "a_city"_h);
		out << std::endl;
		subject.detach(&view);

		// Demonstrate builder
		city_director director{};
		city_builder builder{};
		director.set_city_builder(&builder);
		director.construct_city("my_city"_h, "blue"_h, std::vector<handle>{"montreal"_h});
		auto my_city = director.get_city();
		out << my_city.name << " " << my_city.region << " " << my_city.connections.at(0) << std::endl;
		out << std::endl;

		// Demonstrate decorator
		auto decorator = std::make_unique<decks_decorator>(ctx.decks);
		for (auto card : decorator->get_cards()) {
			out << card << " ";
		}
		auto epidemic_decorator = std::make_unique<epidemic_decks_decorator>(ctx.decks);
		for (auto card : epidemic_decorator->get_cards()) {
			out << card << " ";
		}
		auto event_decorator = std::make_unique<event_decks_decorator>(ctx.decks);
		for (auto card : event_decorator->get_cards()) {
			out << card << " ";
		}
		out << std::endl;

		// Demonstrate strategy
		draw_card_from_top from_top{};
		draw_card_from_bottom from_bottom{};
		draw_card draw{&from_top};
		auto card1 = draw.execute_strategy(ctx.decks, "orange"_h);
		out << card1 << std::endl;
		draw.set_strategy(&from_bottom);
		auto card2 = draw.execute_strategy(ctx.decks, "orange"_h);
		out << card2 << std::endl;
	}
};

#endif //PANDEMIC_PATTERN_H
