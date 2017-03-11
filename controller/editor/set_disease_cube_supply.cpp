#include "set_disease_cube_supply.h"

auto set_disease_cube_supply::name() const->std::string {
	return "set-disease-cube-supply";
}

auto set_disease_cube_supply::description() const->std::string {
	return "Set the number of disease cube supply";
}

auto set_disease_cube_supply::run(context &ctx, const args_t &args, ostream_t &out) const -> void{
	try {
		auto color = args.at(0);
		auto num = std::stoi(args.at(1));
		ctx.game.add_cube_to_supply(color, num);
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << "<color> <count>" << std::endl;
	}
}