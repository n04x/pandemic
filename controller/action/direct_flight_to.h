#ifndef PANDEMIC_DIRECT_FLIGHT_TO_H
#define PANDEMIC_DIRECT_FLIGHT_TO_H

#include "../../command.h"

struct direct_flight_to : command {

	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override;
};

#endif // !PANDEMIC_DIRECT_FLIGHT_TO_H
