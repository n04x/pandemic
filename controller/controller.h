#ifndef PANDEMIC_CONTROLLER_H
#define PANDEMIC_CONTROLLER_H

#include <iosfwd>
#include <string>
#include <vector>
#include <ostream>
#include "../context.h"

// controller represents a game action.
struct controller {
	using args_t = std::vector<std::string>;

	using ostream_t = std::ostream;

	virtual ~controller() = default;

	controller() = default;

	controller(controller const &) = default;

	controller(controller &&) = default;

	virtual auto operator=(controller const &) -> controller & = default;

	virtual auto operator=(controller &&) -> controller & = default;

	// name returns the name of the command. Used to execute the command.
	virtual auto name() const -> std::string = 0;

	// description returns a description of the command. Used in help.
	virtual auto description() const -> std::string = 0;

	// run executes the command with the given context and arguments.
	virtual auto run(context &ctx, args_t const &args, ostream_t &out) const -> void = 0;
};

#endif //PANDEMIC_CONTROLLER_H
