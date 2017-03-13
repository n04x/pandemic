#ifndef PANDEMIC_CREATE_DECK_H
#define PANDEMIC_CREATE_DECK_H

#include "../../command.h"

struct create_deck : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &c, args_type const &args, ostream_type &out) const -> void override;
};

#endif //PANDEMIC_CREATE_DECK_H
