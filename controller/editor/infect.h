#ifndef PANDEMIC_INFECT_H
#define PANDEMIC_INFECT_H
#include "../controller.h"

struct infect : controller {

	virtual auto name() const->std::string override;
	virtual auto description() const->std::string override;
	virtual auto run(context &ctx, const args_t &args, ostream_t &out) const->void override;

};
#endif // !PANDEMIC_INFECT_H
