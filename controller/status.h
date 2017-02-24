#ifndef PANDEMIC_STATUS_H
#define PANDEMIC_STATUS_H

#include "controller.h"

struct status : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &c, controller::args_t const &args) const -> void override;
};

#endif //PANDEMIC_STATUS_H
