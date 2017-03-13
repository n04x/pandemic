#include "place_research_station.h"

auto place_research_station::name() const -> std::string {
	return "place-research-station";
}

auto place_research_station::description() const -> std::string {
	return "Place a research station on map";
}

auto place_research_station::run(context &ctx, args_t const &args, ostream_t &out) const -> void {
	try {
		auto name = args.at(0);
		if (ctx.cities.has_research_station(name) == false) {
			ctx.game.remove_research_station_supply();
			ctx.cities.place_research_station(name);
		}

	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<city>" << std::endl;
	}
}