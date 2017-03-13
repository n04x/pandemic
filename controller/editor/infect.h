#ifndef PANDEMIC_INFECT_H
#define PANDEMIC_INFECT_H

#include "../../command.h"

struct infect : command {

	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, const args_type &args, ostream_type &out) const -> void override;

};

#endif // !PANDEMIC_INFECT_H
