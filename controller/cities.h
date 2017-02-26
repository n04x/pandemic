#ifndef PANDEMIC_CITIES_H
#define PANDEMIC_CITIES_H

#include "controller.h"

struct cities : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_CITIES_H
