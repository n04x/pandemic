#include <fstream>
#include "reference_card.h"

auto reference_card::name() const -> std::string {
	return "reference-card";
}

auto reference_card::description() const -> std::string {
	return "Print reference card";
}

auto reference_card::run(context &c) const -> void {
	std::ifstream s("../text/reference_card.md");
	if (!s.is_open()) {
		throw "could not open reference card";
	}
	c.out << s.rdbuf() << std::endl;
}