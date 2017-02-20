#include "Cards.h"
#include <time.h>
#include <stdlib.h>	


// ======================================================
// Method to draw a Role Card at the start of the game.
// ======================================================
string Cards::DrawRole()
{
		int RandInt = (rand() % NUMBER_ROLE_CARDS);  // Based on the number of roles in the Cards.h and draw one in the array.
		string TempCard = RoleCard[RandInt];// It going to draw a random card in the Role Cards Array and assign to the TempCard variable

		
		return TempCard; // return the result in the TempCard string
}

// ==============================================
// Method to draw a Location Card
// ==============================================
string Cards::DrawLocation()
{
	int RandInt = (rand() % NUMBER_LOCATION_CARDS);
	string TempCard = LocationCard[RandInt];


	return TempCard; 
}

// ======================================================
// Method to draw an Event Card
// ======================================================
string Cards::DrawEvent()
{
	int RandInt = (rand() % NUMBER_EVENT_CARDS);
	string TempCard = EventCard[RandInt];


	return TempCard; 
}

// ======================================================
// Method to draw an Epidemic Card
// ======================================================
string Cards::DrawEpidemic()
{
	
	int RandInt = (rand() % NUMBER_EPIDEMIC_CARDS);
	string TempCard = EpidemicCards[RandInt];


	return TempCard;
}
// ======================================================
// This method draw a random card DURING the game
// ======================================================
string Cards::DrawCard()
{
	int RandInt = (rand() % 3);  // RANDOM It will randomly choose a style of card to draw 

	if (RandInt == 2) // Location Cards
	{
		string TempCard = DrawLocation();
		return TempCard;
	}
	else if (RandInt == 1) // Epidemic Cards
	{
		string TempCard = DrawEpidemic();
		return TempCard;
	}
	else // Event Cards
	{
		string TempCard = DrawEvent();
		return TempCard;
	}
	
}
// **************************************************************
// This method draw a random card at the START of the game
// since in the rules you can't start by drawing epidimic card
// **************************************************************
string Cards::DrawStarterCard()
{
	int RandInt = (rand() % 2);  // RANDOM It will randomly choose a style of card to draw 

	if (RandInt == 0) // Location Cards
	{
		string TempCard = DrawLocation();
		return TempCard;
	}
	else // Event Cards
	{
		string TempCard = DrawEvent();
		return TempCard;
	}

}