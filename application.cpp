#include "application.h"
#include "controller/reference_card.h"
#include "controller/begin.h"
#include "view/status.h"
#include "view/cities.h"
#include "controller/place_pawn.h"
#include "controller/editor/add_city.h"
#include "view/show_deck.h"
#include "view/players.h"
#include "controller/end.h"
#include "controller/editor/add_player.h"
#include "controller/editor/create_deck.h"
#include "controller/editor/shuffle_deck.h"
#include "controller/editor/add_to_deck.h"
#include "controller/editor/move_top_card.h"
#include "controller/editor/give_role.h"
#include "controller/editor/add_cities_to_deck.h"
#include "controller/editor/place_research_station.h"
#include "controller/editor/set_research_station_supply.h"
#include "controller/editor/set_disease_cube_supply.h"
#include "controller/editor/infect.h"
#include "controller/action/direct_flight_to.h"
#include "controller/action/drive_to.h"
#include "controller/action/shuttle_flight_to.h"
#include "controller/action/charter_flight_to.h"
#include "controller/action/treat_disease.h"
#include "controller/action/share_knowledge_to.h"
#include "controller/action/share_knowledge_from.h"
#include "controller/action/discover_cure.h"
#include "controller/editor/validate_city_connections.h"
#include "controller/action/play_event.h"
#include "controller/action/move_player.h"
#include "controller/action/store_event.h"
#include "controller/pattern.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <set>
#include <random>

application::application(std::istream &in, std::ostream &out) :
		in{in},
		out{out},
		ctx{},
		commands{},
		command_history{} {
	insert_command<pattern_driver>("setup");
	insert_command<reference_card>("view");
	insert_command<status>("view");
	insert_command<cities>("view");
	insert_command<place_pawn>("setup");
	insert_command<add_city>("setup");
	insert_command<show_deck>("view");
	insert_command<players>("view");
	insert_command<begin>("turn");
	insert_command<end_actions>("turn");
	insert_command<add_player>("setup");
	insert_command<create_deck>("setup");
	insert_command<shuffle_deck>("setup");
	insert_command<add_to_deck>("setup");
	insert_command<move_top_card>("setup");
	insert_command<give_role>("setup");
	insert_command<add_cities_to_deck>("setup");
	insert_command<place_research_station>("setup");
	insert_command<set_research_station_supply>("setup");
	insert_command<set_disease_cube_supply>("setup");
	insert_command<infect>("setup");
	insert_command<direct_flight_to>("action");
	insert_command<drive_to>("action");
	insert_command<shuttle_flight_to>("action");
	insert_command<charter_flight_to>("action");
	insert_command<treat_disease>("action");
	insert_command<share_knowledge_to>("action");
	insert_command<share_knowledge_from>("action");
	insert_command<discover_cure>("action");
	insert_command<validate_city_connections>("setup");
	insert_command<play_event>("action");
	insert_command<move_player>("action");
	insert_command<store_event>("action");
};

auto application::help() -> void {
	static constexpr auto col1 = 30;
	static constexpr auto fill = ' ';
	// Get list of command categories
	std::set<std::string> categories;
	for (auto const &i : category_commands) {
		categories.insert(i.first);
	}
	// Print help for each command in category
	auto iterations = 0u;
	for (auto const &category : categories) {
		out << category << std::endl;
		auto const &range = category_commands.equal_range(category);
		for (auto it = range.first; it != range.second; it++) {
			auto const &name = it->second;
			auto const &search = commands.find(name);
			if (search == commands.end()) {
				out << "ERROR: could not get object for command '" << name << "'" << std::endl;
				continue;
			}
			auto const &command = search->second;
			out << "   ";
			out << std::left << std::setw(col1) << std::setfill(fill) << command->name();
			out << command->description();
			out << std::endl;
		}
		if (++iterations < categories.size()) {
			out << std::endl;
		}
	}
}

auto application::invalid_command(std::string const &command) -> void {
	out << "'" << command << "'" << " is not a valid command" << std::endl;
}

auto application::prompt() -> void {
	auto const &player = ctx.players.get_current_turn();
	if (player == ""_h) {
		out << "> ";
		return;
	}
	out << player << "> ";
}

auto application::intro() -> void {
	static constexpr auto banner = R"(
                        _                _
  _ __   __ _ _ __   __| | ___ _ __ ___ (_) ___
 | '_ \ / _` | '_ \ / _` |/ _ \ '_ ` _ \| |/ __|
 | |_) | (_| | | | | (_| |  __/ | | | | | | (__
 | .__/ \__,_|_| |_|\__,_|\___|_| |_| |_|_|\___|
 |_|
)";
	out << banner << std::endl;
}

auto application::run() -> void {
	intro();
	prompt();
	// Read input line from user
	std::string line;
	while (std::getline(in, line)) {
		std::string name;
		auto code = call_command(line, name, out);
		// Handle return code from command
		if (code == return_code::blank_input) {
			prompt();
			continue;
		}
		if (code == return_code::not_found) {
			invalid_command(name);
			prompt();
			continue;
		}
		if (code == return_code::exit) {
			break;
		}
		// Auto save
		if (seed != 0) {
			auto filename = "save-" + std::to_string(seed);
			save(filename);
		}
		prompt();
	}
}

auto print_win(std::ostream &out) -> void {
	static constexpr auto banner = R"(
 __   __                     _         _
 \ \ / /__  _   _  __      _(_)_ __   | |
  \ V / _ \| | | | \ \ /\ / / | '_ \  | |
   | | (_) | |_| |  \ V  V /| | | | | |_|
   |_|\___/ \__,_|   \_/\_/ |_|_| |_| (_)
)";
	out << banner << std::endl;
	out << "All four cures has been discovered. Humanity is safe... for now." << std::endl;
}

auto print_lose(std::ostream &out, std::string const &message) -> void {
	static constexpr auto banner = R"(
 __   __            _                       __
 \ \ / /__  _   _  | | ___  ___  ___   _   / /
  \ V / _ \| | | | | |/ _ \/ __|/ _ \ (_) | |
   | | (_) | |_| | | | (_) \__ \  __/  _  | |
   |_|\___/ \__,_| |_|\___/|___/\___| (_) | |
                                           \_\
)";
	out << banner << std::endl;
	out << message << std::endl;
}

auto application::call_command(std::string const &command, std::string &name, std::ostream &out) -> return_code {
	// Split command into tokens
	std::istringstream iss{command};
	if (!(iss >> name)) {
		return return_code::blank_input;
	}
	std::vector<std::string> args;
	std::string arg;
	while (iss >> arg) {
		args.emplace_back(arg);
	}
	// Handle command name
	if (name == "#" || name == "seed") {
		// Ignore line
		return return_code::ok;
	}
	if (name == "exit") {
		return return_code::exit;
	}
	if (name == "help") {
		help();
	} else if (name == "save") {
		if (args.empty()) {
			out << "usage: save <filename>" << std::endl;
			return return_code::ok;
		}
		auto const &filename = args.at(0);
		save(filename);
	} else if (name == "load") {
		std::string filename{"default"};
		if (!args.empty()) {
			filename = args.at(0);
		}
		load(filename);
	}
	else if (name == "replay") {
		std::string filename{ "default" };
		if (!args.empty()) {
			filename = args.at(0);
		}
		replay(filename);
	}
	else {
		try {
			// Ensure player has enough actions remaining
			auto category = command_category(name);
			if (category == "action" && ctx.players.get_actions_remaining() == 0) {
				out << name << ": out of actions" << std::endl;
				return return_code::ok;
			}
			// Run command and push into history
			auto const &controller = commands.at(name);
			commands.at(name)->run(ctx, args, out);
			command_history.push_back(command);
		} catch (std::out_of_range const &) {
			return return_code::not_found;
		}
	}
	if (game_end()) {
		return return_code::exit;
	}
	return return_code::ok;
}

auto application::game_end() -> bool {
	if (ctx.game.all_cures_discovered()) {
		print_win(out);
		return true;
	}
	if (ctx.game.outbreak_limit_reached()) {
		print_lose(out, "Worldwide panic! Outbreaks marker reached last space of Outbreaks Track!");
		return true;
	}
	if (ctx.game.out_of_cubes()) {
		print_lose(out, "Disease spread too much! Unable to place number of disease cubes needed on the board!");
		return true;
	}
	if (ctx.decks.remove_failed("player"_h)) {
		print_lose(out, "Out of time! Can not draw 2 Player cards after doing actions!");
		return true;
	}
	return false;
}

auto application::command_category(std::string const &command) -> std::string {
	for (auto const &pair : category_commands) {
		if (pair.second == command) {
			return pair.first;
		}
	}
	return "";
}

auto application::save(std::string const &filename) -> void {
	auto path = "../script/" + filename + ".pandemic.txt";
	std::ofstream out;
	out.open(path);
	for (auto const &line : command_history) {
		out << line << std::endl;
	}
}

struct null_buffer : std::streambuf {
	inline auto overflow(int c) -> int {
		return c;
	}
};

auto application::load(std::string const &filename) -> void {
	auto path = "../script/" + filename + ".pandemic.txt";
	std::ifstream in{path};
	if (!in.is_open()) {
		out << "could not open file '" << path << "'" << std::endl;
		return;
	}
	// Suppress command output
	null_buffer nb;
	std::ostream null_stream{&nb};
	std::string line;
	bool after_first_line{false};
	// Run commands by line
	while (std::getline(in, line)) {
		if (!after_first_line) {
			after_first_line = true;
			// Split command into tokens
			std::istringstream iss{line};
			std::string name;
			if (!(iss >> name)) {
				continue;
			}
			std::vector<std::string> args;
			std::string arg;
			while (iss >> arg) {
				args.emplace_back(arg);
			}
			if (name == "seed") {
				auto const &seed = args.at(0);
				auto s = std::stoul(seed);
				ctx.decks.set_seed(s);
				this->seed = s;
				out << "using existing seed '" << s << "'" << std::endl;
			} else {
				std::random_device r;
				std::default_random_engine e{r()};
				auto seed = e();
				if (ctx.decks.set_seed(seed)) {
					this->seed = seed;
					auto cmd = "seed " + std::to_string(seed);
					command_history.push_back(cmd);
					out << "using new seed '" << seed << "'" << std::endl;
				}
			}
		}
		std::string name;
		auto code = call_command(line, name, null_stream);
		if (code == return_code::blank_input) {
			continue;
		}
		if (code == return_code::not_found) {
			invalid_command(name);
			continue;
		}
	}
}
// replay command to replay the two bonus file.
auto application::replay(std::string const & filename) -> void
{
	auto path = "../script/" + filename + ".pandemic.txt";
	std::ifstream in{ path };
	if (!in.is_open()) {
		out << "could not open file '" << path << "'" << std::endl;
		return;
	}
	// Suppress command output
	null_buffer nb;
	std::ostream null_stream{ &nb };
	std::string line;
	bool after_first_line{ false };
	// Run commands by line
	while (std::getline(in, line)) {
		//out << "file " << line << std::endl;
		if (!after_first_line) {
			after_first_line = true;
			// Split command into tokens
			std::istringstream iss{ line };
			std::string name;
			if (!(iss >> name)) {
				continue;
			}
			std::vector<std::string> args;
			std::string arg;
			
			while (iss >> arg) {
				args.emplace_back(arg);
			}
			if (name == "seed") {
				auto const &seed = args.at(0);
				auto s = std::stoul(seed);
				ctx.decks.set_seed(s);
				this->seed = s;
				out << "using existing seed '" << s << "'" << std::endl;
			}
			else {
				std::random_device r;
				std::default_random_engine e{ r() };
				auto seed = e();
				if (ctx.decks.set_seed(seed)) {
					this->seed = seed;
					auto cmd = "seed " + std::to_string(seed);
					command_history.push_back(cmd);
					out << "using new seed '" << seed << "'" << std::endl;
				}
			}
		}
		std::string name;
		if (line.find("load") != std::string::npos) {
			line = "replay" + line.substr(4);
		}
		if (!(line.find("#") != std::string::npos) && !(line == "")) {
			out << "commands: " << line << std::endl;
		}
		auto code = call_command(line, name, null_stream);
		if (code == return_code::blank_input) {
			continue;
		}
		if (code == return_code::not_found) {
			invalid_command(name);
			continue;
		}
	}
}
