#include "application.h"
#include "command/reference_card.h"
#include "command/setup.h"
#include "command/status.h"
#include <iomanip>
#include <sstream>

application::application(std::istream &in, std::ostream &out) :
		in{in},
		out{out},
		c{out},
		commands() {
	make_command<reference_card>();
	make_command<setup>();
	make_command<status>();
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
	for (std::string line; std::getline(in, line);) {
		std::istringstream iss(line);
		std::string com;
		if (!(iss >> com)) {
			throw "unexpected input error";
		}
		if (com == "exit") {
			break;
		} else if (com == "help") {
			help();
		} else {
			try {
				commands.at(com)->run(c);
			} catch (std::out_of_range const &) {
				invalid_command(com);
			}
		}
		prompt();
	}
}
