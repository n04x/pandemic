#ifndef PANDEMIC_REFERENCE_CARD_H
#define PANDEMIC_REFERENCE_CARD_H

#include "../command.h"

struct reference_card : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override;
};

#endif //PANDEMIC_REFERENCE_CARD_H
