#ifndef PANDEMIC_REFERENCE_CARD_H
#define PANDEMIC_REFERENCE_CARD_H

#include "controller.h"

struct reference_card : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, controller::args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_REFERENCE_CARD_H
