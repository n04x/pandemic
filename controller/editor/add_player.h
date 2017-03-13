#ifndef PANDEMIC_ADD_PLAYER_H
#define PANDEMIC_ADD_PLAYER_H

#include "../controller.h"

struct add_player : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &c, args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_ADD_PLAYER_H
