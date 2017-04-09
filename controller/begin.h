#ifndef PANDEMIC_BEGIN_PLAY_H
#define PANDEMIC_BEGIN_PLAY_H

#include "../command.h"

struct begin : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override;
};

#endif //PANDEMIC_BEGIN_PLAY_H
