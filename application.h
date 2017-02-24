#ifndef PANDEMIC_APPLICATION_H
#define PANDEMIC_APPLICATION_H

#include <istream>
#include <ostream>
#include <string>
#include <memory>
#include <unordered_map>
#include "controller/controller.h"

// application handles user input and output.
struct application {

	application(std::istream &in, std::ostream &out);

	// run starts the game loop. It returns when the user exits the game.
	auto run() -> void;

private:
	auto help() -> void;

	auto invalid_command(std::string const &command) -> void;

	auto prompt() -> void;

	auto intro() -> void;

	template<class T>
	auto insert_controller() -> void {
		auto com = std::make_unique<T>();
		controllers.insert(std::make_pair(com->name(), std::move(com)));
	}

	std::istream &in;
	std::ostream &out;
	context ctx;
	std::unordered_map<std::string, std::unique_ptr<controller>> controllers;
};

#endif //PANDEMIC_APPLICATION_H
