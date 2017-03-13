#pragma once

#include "../controller.h"

class share_knowledge_from :
		public controller {
public:
	// name returns the name of the command. Used to execute the command.
	virtual auto name() const -> std::string;

	// description returns a description of the command. Used in help.
	virtual auto description() const -> std::string;

	// run executes the command with the given context and arguments.
	virtual auto run(context &ctx, args_t const &args, ostream_t &out) const -> void;

};

