#include "application.h"
#include "controller/reference_card.h"
#include "controller/setup.h"
#include "controller/status.h"
#include "controller/load.h"
#include "controller/cities.h"
#include "controller/place_pawn.h"
#include "controller/save.h"
#include <iomanip>
#include <sstream>

application::application(std::istream &in, std::ostream &out) :
		in{in},
		out{out},
		ctx{out},
		controllers{} {
	insert_controller<reference_card>();
	insert_controller<setup>();
	insert_controller<status>();
	insert_controller<load>();
	insert_controller<save>();
	insert_controller<cities>();
	insert_controller<place_pawn>();
};

auto application::help() -> void {
	static constexpr auto col1 = 16;
	static constexpr auto fill = ' ';
	for (auto const &i : controllers) {
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
				controllers.at(com)->run(ctx, args);
			} catch (std::out_of_range const &) {
				invalid_command(com);
			}
		}
		prompt();
	}
}
