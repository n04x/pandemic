#include "application.h"
#include "command/reference_card.h"
#include "command/setup.h"
#include "command/status.h"
#include "command/load.h"
#include "command/cities.h"
#include "command/place_pawn.h"
#include "command/save.h"
#include <iomanip>
#include <sstream>

application::application(std::istream &in, std::ostream &out) :
		in{in},
		out{out},
		c{out},
		commands() {
	insert_command<reference_card>();
	insert_command<setup>();
	insert_command<status>();
	insert_command<load>();
	insert_command<save>();
	insert_command<cities>();
	insert_command<place_pawn>();
};

auto application::help() -> void {
	static constexpr auto col1 = 16;
	static constexpr auto fill = ' ';
	for (auto const &i : commands) {
		out << std::left << std::setw(col1) << std::setfill(fill) << i.second->name();
		out << i.second->description();
		out << std::endl;
	}
}

auto application::invalid_command(std::string const &command) -> void {
	out << "'" << command << "'" << " is not a valid command" << std::endl;
}

auto application::prompt() -> void {
	out << "$ ";
}

auto application::intro() -> void {
	static constexpr auto banner = R"(
                        _                _
  _ __   __ _ _ __   __| | ___ _ __ ___ (_) ___
 | '_ \ / _` | '_ \ / _` |/ _ \ '_ ` _ \| |/ __|
 | |_) | (_| | | | | (_| |  __/ | | | | | | (__
 | .__/ \__,_|_| |_|\__,_|\___|_| |_| |_|_|\___|
 |_|                                            )";
	out << banner << std::endl << std::endl;
}

auto application::run() -> void {
	intro();
	prompt();
	std::string line;
	while (std::getline(in, line)) {
		// use stream to tokenize line
		std::istringstream iss{line};
		std::string com;
		if (!(iss >> com)) {
			throw "unexpected input error";
		}
		if (com == "exit") {
			break;
		} else if (com == "help") {
			help();
		} else {
			// read command arguments
			std::vector<std::string> args;
			std::string arg;
			while (iss >> arg) {
				args.emplace_back(arg);
			}
			// run command
			try {
				commands.at(com)->run(c, args);
			} catch (std::out_of_range const &) {
				invalid_command(com);
			}
		}
		prompt();
	}
}
