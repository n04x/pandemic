#ifndef PANDEMIC_BEGIN_PLAY_H
#define PANDEMIC_BEGIN_PLAY_H

#include "controller.h"

struct begin_play : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_BEGIN_PLAY_H
