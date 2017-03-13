#ifndef PANDEMIC_CITIES_H
#define PANDEMIC_CITIES_H

#include "../command.h"

struct cities : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void override;
};

#endif //PANDEMIC_CITIES_H
