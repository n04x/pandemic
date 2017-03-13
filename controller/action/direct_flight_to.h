#ifndef PANDEMIC_DIRECT_FLIGHT_TO_H
#define PANDEMIC_DIRECT_FLIGHT_TO_H

#include "../controller.h"

struct direct_flight_to : controller {

	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_t const &args, ostream_t &out) const -> void override;
};

#endif // !PANDEMIC_DIRECT_FLIGHT_TO_H
