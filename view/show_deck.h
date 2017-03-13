#ifndef PANDEMIC_SHOW_DECK_H
#define PANDEMIC_SHOW_DECK_H

#include "../command.h"

struct show_deck : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override;
};

#endif //PANDEMIC_SHOW_DECK_H
