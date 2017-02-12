#include "setup.h"

auto setup::name() const -> std::string {
	return "setup";
}

auto setup::description() const -> std::string {
	return "Setup the game";
}

auto setup::run(context &c) const -> void {
	c.p.add_player("red"_h);
	c.p.set_role("red"_h, "dispatcher"_h);
	c.p.add_player("blue"_h);
	c.p.set_role("blue"_h, "scientist"_h);
}