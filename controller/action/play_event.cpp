#include "play_event.h"


auto play_event::name() const -> std::string
{
	return "play-event";
}

auto play_event::description() const -> std::string
{
	return "Play event card from any player's hand (Does not count as a action)";
}

auto play_event::run(context & ctx, args_type const & args, ostream_type & out) const -> void
{
	try {
		auto player = args.at(0);	//Player with event card
		auto event = args.at(1);	//Event card
		auto playerDiscard = "player_discard"_h;
		auto infectionDiscard = "infection_discard"_h;
		auto infectionDeck = "infection"_h;

		for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {	//Check all cards in player's hand
			if (*card == event) {	//if card found

				if (event == "airlift"_h) {
					try {
						auto playerMove = args.at(2);	//Player to move
						auto city = args.at(3);	//City to go to

						ctx.players.set_city(playerMove, city);	// Set the new position of player
						ctx.decks.remove(player, event);
						ctx.decks.add_to_top(playerDiscard, event);
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " <player_with_card> airlift <player_to_move> <city>" << std::endl;
					}
				}

				if (event == "forecast"_h) {	//TODO Figure out why after placing all cards in deck current player name comes up twice
					try {

						auto a = ctx.decks.remove_from_top(infectionDeck);
						auto b = ctx.decks.remove_from_top(infectionDeck);
						auto c = ctx.decks.remove_from_top(infectionDeck);
						auto d = ctx.decks.remove_from_top(infectionDeck);
						auto e = ctx.decks.remove_from_top(infectionDeck);
						auto f = ctx.decks.remove_from_top(infectionDeck);

						out << "1. "<< a << " 2. " << b << " 3. " << c << " 4. " << d << " 5. " << e << " 6. " << f << std::endl;

						out << "Reorder the cards above by number from sixth to first (press enter between numbers):" << std::endl;

						std::vector<int> cards;

						for (int i = 1; i <= 6; i++)	//Change integer to 0 if number already used
							cards.push_back(i);

						for (int i = 0; i < 6; i++) {

							int x = 0;
							
							while ((x > 6) || (x < 1)) {
								
								std::cin >> x;

								while ((x > 6) || (x < 1) || (cards[x - 1] == 0)) {
									
									while ((x > 6) || (x < 1)) {
										out << "Wrong number! Try Again!" << std::endl;
										std::cin >> x;
									}
									
									while (cards[x - 1] == 0){
										out << "Card already put back in deck! Chose another card!" << std::endl;
										std::cin >> x;

										while ((x > 6) || (x < 1)) {
											out << "Wrong number! Try Again!" << std::endl;
											std::cin >> x;
										}
									}	
								}

								if (x == 1) {
									ctx.decks.add_to_top(infectionDeck, a);
									cards[0] = 0;
								}
									

								if (x == 2){
									ctx.decks.add_to_top(infectionDeck, b);
									cards[1] = 0;
								}

								if (x == 3){
									ctx.decks.add_to_top(infectionDeck, c);
									cards[2] = 0;
								}

								if (x == 4) {
									ctx.decks.add_to_top(infectionDeck, d);
									cards[3] = 0;
								}

								if (x == 5){
									ctx.decks.add_to_top(infectionDeck, e);
									cards[4] = 0;
								}

								if (x == 6){
									ctx.decks.add_to_top(infectionDeck, f);
									cards[5] = 0;
								}

								if ((x > 6) || (x < 1))
									out << "Wrong number! Try Again!" << std::endl;
							}
						}

						ctx.decks.remove(player, event);
						ctx.decks.add_to_top(playerDiscard, event);
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " <player_with_card> forecast" << std::endl;
					}

				}

				if (event == "government_grant"_h) {
					try {
						auto city = args.at(2);	//City to add research station

						if (ctx.cities.has_research_station(city) == false) {	//Check if research station exists
							ctx.game.remove_research_station_supply();
							ctx.cities.place_research_station(city);
							ctx.decks.remove(player, event);
							ctx.decks.add_to_top(playerDiscard, event);
						}

						else
							out << "City already has a research station!" << std::endl;
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " <player_with_card> government_grant <city>" << std::endl;
					}
				}

				if (event == "one_quiet_night"_h) {

					try {
					
						//TODO One Quiet Night
						
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " one_quiet_night" << std::endl;
					}

				}

				if (event == "resilient_population"_h) {

					try {
						auto infCard = args.at(2);	//Infection card to remove from play
						
						for (auto card = ctx.decks.begin(infectionDiscard); card != ctx.decks.end(infectionDiscard); card++) {
							if (*card == infCard) {
								ctx.decks.remove(infectionDiscard, infCard);	//Completely remove from play card
								ctx.decks.remove(player, event);
								ctx.decks.add_to_top(playerDiscard, event);
								return;
							}
						}

						out << infCard << " is not in the infection discard pile!" << std::endl;	//If no card found
					}
					catch (std::out_of_range const &) {
						out << "usage: " << name() << " <player_with_card> resilient_population <card_to_remove>" << std::endl;
					}
				}

				return;
			}

		}

		//If player is a Contingency Planner check contingency planner deck

		if (ctx.players.get_role(player) == "contingency_planner"_h) {

			auto player = "contingency_planner"_h;

			for (auto card = ctx.decks.begin(player); card != ctx.decks.end(player); card++) {	//Check all cards in player's hand
				if (*card == event) {	//if card found

					if (event == "airlift"_h) {
						try {
							auto playerMove = args.at(2);	//Player to move
							auto city = args.at(3);	//City to go to

							ctx.players.set_city(playerMove, city);	// Set the new position of player
							ctx.decks.remove(player, event);
							ctx.decks.add_to_top(playerDiscard, event);
						}
						catch (std::out_of_range const &) {
							out << "usage: " << name() << " <player_with_card> airlift <player_to_move> <city>" << std::endl;
						}
					}

					if (event == "forecast"_h) {	//TODO Figure out why after placing all cards in deck current player name comes up twice
						try {

							auto a = ctx.decks.remove_from_top(infectionDeck);
							auto b = ctx.decks.remove_from_top(infectionDeck);
							auto c = ctx.decks.remove_from_top(infectionDeck);
							auto d = ctx.decks.remove_from_top(infectionDeck);
							auto e = ctx.decks.remove_from_top(infectionDeck);
							auto f = ctx.decks.remove_from_top(infectionDeck);

							out << "1. " << a << " 2. " << b << " 3. " << c << " 4. " << d << " 5. " << e << " 6. " << f << std::endl;

							out << "Reorder the cards above by number from sixth to first (press enter between numbers):" << std::endl;

							std::vector<int> cards;

							for (int i = 1; i <= 6; i++)	//Change integer to 0 if number already used
								cards.push_back(i);

							for (int i = 0; i < 6; i++) {

								int x = 0;

								while ((x > 6) || (x < 1)) {

									std::cin >> x;

									while ((x > 6) || (x < 1) || (cards[x - 1] == 0)) {

										while ((x > 6) || (x < 1)) {
											out << "Wrong number! Try Again!" << std::endl;
											std::cin >> x;
										}

										while (cards[x - 1] == 0) {
											out << "Card already put back in deck! Chose another card!" << std::endl;
											std::cin >> x;

											while ((x > 6) || (x < 1)) {
												out << "Wrong number! Try Again!" << std::endl;
												std::cin >> x;
											}
										}
									}

									if (x == 1) {
										ctx.decks.add_to_top(infectionDeck, a);
										cards[0] = 0;
									}


									if (x == 2) {
										ctx.decks.add_to_top(infectionDeck, b);
										cards[1] = 0;
									}

									if (x == 3) {
										ctx.decks.add_to_top(infectionDeck, c);
										cards[2] = 0;
									}

									if (x == 4) {
										ctx.decks.add_to_top(infectionDeck, d);
										cards[3] = 0;
									}

									if (x == 5) {
										ctx.decks.add_to_top(infectionDeck, e);
										cards[4] = 0;
									}

									if (x == 6) {
										ctx.decks.add_to_top(infectionDeck, f);
										cards[5] = 0;
									}

									if ((x > 6) || (x < 1))
										out << "Wrong number! Try Again!" << std::endl;
								}
							}

							ctx.decks.remove(player, event);
							ctx.decks.add_to_top(playerDiscard, event);
						}
						catch (std::out_of_range const &) {
							out << "usage: " << name() << " <player_with_card> forecast" << std::endl;
						}

					}

					if (event == "government_grant"_h) {
						try {
							auto city = args.at(2);	//City to add research station

							if (ctx.cities.has_research_station(city) == false) {	//Check if research station exists
								ctx.game.remove_research_station_supply();
								ctx.cities.place_research_station(city);
								ctx.decks.remove(player, event);
								ctx.decks.add_to_top(playerDiscard, event);
							}

							else
								out << "City already has a research station!" << std::endl;
						}
						catch (std::out_of_range const &) {
							out << "usage: " << name() << " <player_with_card> government_grant <city>" << std::endl;
						}
					}

					if (event == "one_quiet_night"_h) {

						try {

							//TODO Copy One Quiet Night event above here

						}
						catch (std::out_of_range const &) {
							out << "usage: " << name() << " one_quiet_night" << std::endl;
						}

					}

					if (event == "resilient_population"_h) {

						try {
							auto infCard = args.at(2);	//Infection card to remove from play

							for (auto card = ctx.decks.begin(infectionDiscard); card != ctx.decks.end(infectionDiscard); card++) {
								if (*card == infCard) {
									ctx.decks.remove(infectionDiscard, infCard);	//Completely remove from play card
									ctx.decks.remove(player, event);
									ctx.decks.add_to_top(playerDiscard, event);
									return;
								}
							}

							out << infCard << " is not in the infection discard pile!" << std::endl;	//If no card found
						}
						catch (std::out_of_range const &) {
							out << "usage: " << name() << " <player_with_card> resilient_population <card_to_remove>" << std::endl;
						}
					}

					return;
				}
			}
		}

		//End Contingency Planner check

		out << event <<" card not found in " << player << "'s hand!" << std::endl;	//If card not found

	}
	catch (std::out_of_range const &) {
		out << "usage: " << name() << " <player_with_card> <card_name>" << std::endl;
	}

}
