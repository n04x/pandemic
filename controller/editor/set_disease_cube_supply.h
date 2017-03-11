#ifndef PANDEMIC_SET_DISEASE_CUBE_SUPPLY_H
#define PANDEMIC_SET_DISEASE_CUBE_SUPPLY_H
#include "../controller.h"

struct set_disease_cube_supply : controller {

	virtual auto name() const->std::string override;
	virtual auto description() const->std::string override;
	virtual auto run(context &ctx, const args_t &args, ostream_t &out) const->void override;
};
#endif // !PANDEMIC_SET_DISEASE_CUBE_SUPPLY_H
