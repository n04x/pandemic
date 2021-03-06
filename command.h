#ifndef PANDEMIC_CONTROLLER_H
#define PANDEMIC_CONTROLLER_H

#include <iosfwd>
#include <string>
#include <vector>
#include <ostream>
#include "context.h"

// command represents a player command.
struct command {
	using args_type = std::vector<std::string>;

	using ostream_type = std::ostream;

	virtual ~command() = default;

	command() = default;

	command(command const &) = default;

	command(command &&) = default;

	virtual auto operator=(command const &) -> command & = default;

	virtual auto operator=(command &&) -> command & = default;

	// name returns the name of the command. Used to execute the command.
	virtual auto name() const -> std::string = 0;

	// description returns a description of the command. Used in help.
	virtual auto description() const -> std::string = 0;

	// run executes the command with the given context and arguments.
	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void = 0;
};

#endif //PANDEMIC_CONTROLLER_H
