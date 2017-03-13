#ifndef PANDEMIC_VALIDATE_CITY_CONNECTIONS_H
#define PANDEMIC_VALIDATE_CITY_CONNECTIONS_H
#include "../controller.h"

struct validate_city_connections : controller {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &c, args_t const &args, ostream_t &out) const -> void override;
};
#endif //PANDEMIC_VALIDATE_CITY_CONNECTIONS_H
