#ifndef PANDEMIC_INFECT_TURN_H
#define PANDEMIC_INFECT_TURN_H

#include "../command.h"

struct infect_turn : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override;
};

#endif //PANDEMIC_INFECT_TURN_H
