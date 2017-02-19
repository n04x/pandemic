#ifndef PANDEMIC_PLACE_PAWN_H
#define PANDEMIC_PLACE_PAWN_H

#include "command.h"

struct place_pawn : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &c, command::args_t const &args) const -> void override;
};

#endif //PANDEMIC_PLACE_PAWN_H
