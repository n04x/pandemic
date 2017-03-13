#include "set_research_station_supply.h"

auto set_research_station_supply::name() const -> std::string {
	return "set-research-station-supply";
}

auto set_research_station_supply::description() const -> std::string {
	return "Set the Research Station Supply";
}

auto set_research_station_supply::run(context &ctx, const args_type &args, ostream_type &out) const -> void {
	try {
		auto name = std::stoi(args.at(0));
		ctx.game.set_research_station_supply(name);
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<count>" << std::endl;
	}
}