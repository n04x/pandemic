#ifndef PANDEMIC_SET_DISEASE_CUBE_SUPPLY_H
#define PANDEMIC_SET_DISEASE_CUBE_SUPPLY_H

#include "../../command.h"

struct set_disease_cube_supply : command {

	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &ctx, const args_type &args, ostream_type &out) const -> void override;
};

#endif // !PANDEMIC_SET_DISEASE_CUBE_SUPPLY_H
