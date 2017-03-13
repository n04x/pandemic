#ifndef PANDEMIC_PLACE_RESEARCH_STATION_H
#define PANDEMIC_PLACE_RESEARCH_STATION_H

#include "../../command.h"

struct place_research_station : command {

	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override;
};

#endif // !PANDEMIC_PLACE_RESEARCH_STATION_H
