#ifndef PANDEMIC_COMMAND_H
#define PANDEMIC_COMMAND_H

#include <iosfwd>
#include <string>
#include "context.h"

struct command {
	virtual ~command() = default;

	command() = default;

	command(command &&) = default;

	command &operator=(command &&) = default;

	command(const command &) = default;

	command &operator=(const command &) = default;

	virtual auto name() const -> std::string = 0;

	virtual auto description() const -> std::string = 0;

	virtual auto run(context &) const -> void = 0;
};


#endif //PANDEMIC_COMMAND_H
