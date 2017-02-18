#include "setup.h"

auto setup::name() const -> std::string {
	return "setup";
}

auto setup::description() const -> std::string {
	return "Setup the game";
}

auto setup::run(context &c) const -> void {
    c.d.create("infection"_h);
    c.d.create("infection_discard"_h);
    c.d.create("player"_h);
    c.d.create("player_discard"_h);
	c.p.add_player("red"_h);
	c.p.set_role("red"_h, "dispatcher"_h);
	c.p.set_city("red"_h, "vancouver"_h);
    c.d.create("red"_h);
	c.p.add_player("blue"_h);
	c.p.set_role("blue"_h, "scientist"_h);
	c.p.set_city("blue"_h, "atlanta"_h);
    c.d.create("red"_h);
}