#ifndef PANDEMIC_SETUP_H
#define PANDEMIC_SETUP_H

#include "command.h"

struct setup : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &) const -> void override;
};

#endif //PANDEMIC_SETUP_H
