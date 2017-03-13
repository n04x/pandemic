#pragma once

#include "../../command.h"

class treat_disease :
		public command {
public:
	// name returns the name of the command. Used to execute the command.
	virtual auto name() const -> std::string;

	// description returns a description of the command. Used in help.
	virtual auto description() const -> std::string;

	// run executes the command with the given context and arguments.
	virtual auto run(context &ctx, args_type const &args, ostream_type &out) const -> void;
};

