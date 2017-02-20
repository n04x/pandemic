#pragma once
#ifndef PLAYERCARDS_H
#define PLAYERCARDS_H
#include <iostream>
#include <string>
using namespace std;


class Cards
{

public:
	string TempCard;
	
	string DrawCard(); // Draw any card
	string DrawStarterCard(); // Draw starter card, Epidemic Cards is excluded.
	
	// If the player needs to draw a specific card
	string DrawLocation();
	string DrawRole();
	string DrawEvent();
	string DrawEpidemic();

	// Number of different styled card
	static const int NUMBER_ROLE_CARDS = 7;
	static const int NUMBER_LOCATION_CARDS = 49;
	static const int NUMBER_EPIDEMIC_CARDS = 6;
	static const int NUMBER_EVENT_CARDS = 5;

	// a array of string for the 7 role cards available to the game
	const string RoleCard[NUMBER_ROLE_CARDS] = { "Scientist","Dispatcher","Researcher","Medic","Quarantine Specialist","Contingency Planner","Operations Expert" };
	// Location Cards Array of String
	const string LocationCard[NUMBER_LOCATION_CARDS] = { "Yangon (Myanmar)", "Bogota (Colombia)", "Jeddah(Saudi Arabia)", "Ahmedabad(India)", "Madrid(Spain)", "Addis Ababa(Ethiopia)", "Abidjan(Ivory Coast)",
		"Delhi(India)", "Surat(india)", "Suzhou(China)", "Shanghai(China)", "Casablanca(Morocco)", "Lima(Peru)", "Sao Paulo(Brazil)", "Tianjin(China)", "Jakarta(Indonesia)",
		"Baghdad(Iraq)", "Saint Petersburg(Russia)", "Nairobi(Kenya)", "Mexico City(Mexico)", "Istanbul(Turkey)", "Tehran(Iran)", "Kinshasa(Congo)", "Jaipur(India)", "Dhaka(Bangladesh)",
		"Guangzhou(China)", "Chennai(India)", "Ho Chi Minh City (Vietnam)", "Kolkata (India)", "Pyongyang (North Korea)", "Santiago (Chile)", "Busan (South Korea)", "Dongguan (China)",
		"Mumba (India)", "Lahore (Pakistan)", "Moscow (Russia)", "Beijing (China)", "New Taipei City (Taiwan)", "London (United Kingdom)", "Shenzhen (China)", "Bangkok (Thailand)",
		"Bangalore(India)", "Riyadh (Saudi Arabia)","Shenyang (China)", "Seoul (South Korea)", "Yokohama(Japan)", "Tokyo(Japan)", "Singapore(Singapore)", "Hong Kong (China)" };
	
	// Epidemic Cards Array of String
	const string EpidemicCards[NUMBER_EPIDEMIC_CARDS] = { "EPIDEMIC CARDS #1", "EPIDEMIC CARDS #2","EPIDEMIC CARDS #3", "EPIDEMIC CARDS #4", "EPIDEMIC CARDS #5", "EPIDEMIC CARDS #6", };

	// Event Cards Array of String
	const string EventCard[NUMBER_EVENT_CARDS] = { "EVENT CARDS: ONE QUIET NIGHT", "EVENT CARDS: FORECAST", "EVENT CARDS: GOVERNMENT GRANT","EVENT CARDS : RESILIENT POPULATION", "EVENT CARDS: AIRLIFT" };



private:
	
};

#endif