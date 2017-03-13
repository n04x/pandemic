#ifndef PANDEMIC_ADD_PLAYER_H
#define PANDEMIC_ADD_PLAYER_H

#include "../../command.h"

struct add_player : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &c, args_type const &args, ostream_type &out) const -> void override;
};

#endif //PANDEMIC_ADD_PLAYER_H
