#ifndef PANDEMIC_APPLICATION_H
#define PANDEMIC_APPLICATION_H

#include <istream>
#include <ostream>
#include <string>
#include "players.h"

struct application {
	application(std::istream &in, std::ostream &out);

	auto run() -> void;

private:
	auto help() -> void;

	auto invalid_command(std::string const &command) -> void;

	auto reference_card() -> void;

	auto prompt() -> void;

	auto intro() -> void;

	auto setup() -> void;

	auto status() -> void;

	std::istream &in;
	std::ostream &out;
	players p;
};

#endif //PANDEMIC_APPLICATION_H
