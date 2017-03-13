#ifndef PANDEMIC_SHUFFLE_DECK_H
#define PANDEMIC_SHUFFLE_DECK_H

#include "../../command.h"

struct shuffle_deck : command {

	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override;
};

#endif // PANDEMIC_SHUFFLE_DECK_H
