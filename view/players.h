#ifndef PANDEMIC_PLAYERS_H
#define PANDEMIC_PLAYERS_H

#include "../command.h"

struct players : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override;
};

#endif //PANDEMIC_PLAYERS_H
