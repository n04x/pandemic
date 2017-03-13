#ifndef PANDEMIC_PLAYERS_H
#define PANDEMIC_PLAYERS_H

#include "../controller.h"

struct players : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_PLAYERS_H
