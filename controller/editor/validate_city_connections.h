#ifndef PANDEMIC_VALIDATE_CITY_CONNECTIONS_H
#define PANDEMIC_VALIDATE_CITY_CONNECTIONS_H
#include "../../command.h"

struct validate_city_connections : command {
	virtual auto name() const -> std::string override;

	virtual auto description() const -> std::string override;

	virtual auto run(context &c, args_type const &args, ostream_type &out) const -> void override;
};
#endif //PANDEMIC_VALIDATE_CITY_CONNECTIONS_H
