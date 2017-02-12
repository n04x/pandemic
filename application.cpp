#include "application.h"
#include <fstream>
#include <vector>
#include <iomanip>
#include <iterator>

application::application(std::istream &in, std::ostream &out) : in(in), out(out), p() {
};

auto application::help() -> void {
	out << "reference-card	Print reference card" << std::endl;
	out << "setup			Setup the game" << std::endl;
	out << "status			Show game status" << std::endl;
	out << "exit			Exit the application" << std::endl;
}

auto application::invalid_command(std::string const &command) -> void {
	out << "'" << command << "'" << " is not a valid command" << std::endl;
}

auto application::reference_card() -> void {
	std::ifstream s("../text/reference_card.md");
	if (!s.is_open()) {
		throw "could not open reference card";
	}
	out << s.rdbuf() << std::endl;
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

auto application::setup() -> void {
	p.add_player("red"_h);
	p.set_role("red"_h, "dispatcher"_h);
	p.add_player("blue"_h);
	p.set_role("blue"_h, "scientist"_h);
}

auto application::status() -> void {
	std::vector<handle> v;
	p.get_players(std::back_inserter(v));
	if (v.empty()) {
		out << "no players" << std::endl;
		return;
	}
	static constexpr auto col1 = 8;
	static constexpr auto col2 = 10;
	static constexpr auto fill = ' ';
	out << std::left << std::setw(col1) << std::setfill(fill) << "PLAYER";
	out << std::left << std::setw(col2) << std::setfill(fill) << "ROLE";
	out << std::endl;
	for (auto i : v) {
		auto role = p.get_role(i);
		out << std::left << std::setw(col1) << std::setfill(fill) << i;
		out << std::left << std::setw(col2) << std::setfill(fill) << role;
		out << std::endl;
	}
}

auto application::run() -> void {
	std::string token;
	intro();
	prompt();
	while (in >> token) {
		if (token == "help" || token == "commands") {
			help();
		} else if (token == "reference-card") {
			reference_card();
		} else if (token == "setup") {
			setup();
		} else if (token == "s" || token == "status") {
			status();
		} else if (token == "exit") {
			break;
		} else {
			invalid_command(token);
		}
		prompt();
	}
}
