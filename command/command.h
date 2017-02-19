#ifndef PANDEMIC_COMMAND_H
#define PANDEMIC_COMMAND_H

#include <iosfwd>
#include <string>
#include <vector>
#include "../context.h"

// command represents a game action.
struct command {
	using args_t = std::vector<std::string>;

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
	virtual auto run(context &c, args_t const &args) const -> void = 0;
};

#endif //PANDEMIC_COMMAND_H
