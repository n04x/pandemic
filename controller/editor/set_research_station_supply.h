#ifndef PANDEMIC_SET_RESEARCH_STATION_SUPPLY_H
#define PANDEMIC_SET_RESEARCH_STATION_SUPPLY_H

#include "../../command.h"

struct set_research_station_supply : command {

	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, const args_type &args, ostream_type &out) const -> void override;
};

#endif // !PANDEMIC_SET_RESEARCH_STATION_SUPPLY_H
