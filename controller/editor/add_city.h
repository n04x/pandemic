#ifndef PANDEMIC_EDIT_CITY_H
#define PANDEMIC_EDIT_CITY_H

#include "../controller.h"

struct add_city : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &c, args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_EDIT_CITY_H
