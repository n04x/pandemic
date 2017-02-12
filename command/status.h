#ifndef PANDEMIC_STATUS_H
#define PANDEMIC_STATUS_H

#include "command.h"

struct status : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &) const -> void override;
};

#endif //PANDEMIC_STATUS_H
