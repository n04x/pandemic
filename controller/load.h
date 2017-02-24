#ifndef PANDEMIC_LOAD_H
#define PANDEMIC_LOAD_H

#include "controller.h"

struct load : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &c, controller::args_t const &args) const -> void override;
};

#endif //PANDEMIC_LOAD_H
