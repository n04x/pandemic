#ifndef PANDEMIC_SAVE_H
#define PANDEMIC_SAVE_H

#include "controller.h"

struct save : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, controller::args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_SAVE_H
