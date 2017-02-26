#ifndef PANDEMIC_SETUP_H
#define PANDEMIC_SETUP_H

#include "controller.h"

struct setup : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_SETUP_H
