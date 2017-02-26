#include "load.h"
#include <fstream>
#include <sstream>
#include <string>

auto load::name() const -> std::string {
	return "load";
}

auto load::description() const -> std::string {
	return "Load map";
}

auto load::run(context &ctx, controller::args_t const &args, ostream_t &out) const -> void {
	std::string filename{"../data/default.panmap.txt"};
	if (!args.empty()) {
		filename = args.at(0);
	}
	std::ifstream s{filename};
	if (!s.is_open()) {
		out << "could not open map file '" << filename << "'" << std::endl;
		return;
	}
	std::string line;
	while (std::getline(s, line)) {
		// use stream to tokenize line
		std::istringstream iss{line};
		std::string color;
		iss >> color;
		std::string name;
		iss >> name;
		ctx.cities.add_city(color, name);
		std::string connection;
		while (iss >> connection) {
			ctx.cities.connect_city(name, connection);
		}
	}
}