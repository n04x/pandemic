#ifndef PANDEMIC_SET_RESEARCH_STATION_SUPPLY_H
#define PANDEMIC_SET_RESEARCH_STATION_SUPPLY_H

#include "../controller.h"

struct set_research_station_supply : controller {

	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, const args_t &args, ostream_t &out) const -> void override;
};

#endif // !PANDEMIC_SET_RESEARCH_STATION_SUPPLY_H
