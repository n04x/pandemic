#ifndef PANDEMIC_PLACE_PAWN_H
#define PANDEMIC_PLACE_PAWN_H

#include "controller.h"

struct place_pawn : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_PLACE_PAWN_H
