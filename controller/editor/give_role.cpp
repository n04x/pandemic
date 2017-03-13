#include "give_role.h"
#include <vector>


auto give_role::name() const -> std::string {
	return "give-role";
}

auto give_role::description() const -> std::string {
	return "Give random role to player";
}

auto give_role::run(context &ctx, args_type const &args, ostream_type &out) const -> void    //TODO Random seed
{
	try {

		auto playerName = args.at(0);

		auto playerRole = ctx.players.get_role(playerName);

		if (!(playerRole == ""_h)) {
			out << "Role already exists" << std::endl;
			return;
		}

		std::vector<handle> existingRoles;

		for (auto iterator : ctx.players) {    //Don't assign existing roles
			auto playerName = iterator.first;
			auto playerRole = ctx.players.get_role(playerName);

			existingRoles.push_back(playerRole);
		}

		std::vector<handle> possibleRoles = {"Dispatcher"_h, "Scientist"_h, "Medic"_h, "Quarantine"_h, "Operations"_h,
											 "Contingency"_h, "Research"_h};    //TODO Check Role Names are correct

		for (auto iterator : existingRoles) {
			std::remove(possibleRoles.begin(), possibleRoles.end(), iterator);
		}

		std::random_shuffle(possibleRoles.begin(), possibleRoles.end());

		ctx.players.set_role(args.at(0), possibleRoles[0]);
	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player>" << std::endl;
	}

}
