#ifndef _PLAYERSCOMPUTER_
#define _PLAYERSCOMPUTER_

#include <iostream>
#include <string>
#include <list>
#include <array>
#include <set>
#include "Players.h"
#include "Card.h"
#include "Command.h"

class PlayersComputer : public Players { //inherits from Players
public:
	PlayersComputer();
	~PlayersComputer();
	PlayersComputer( Players& copyPlayer );
	void DoAction (bool &firstTurn, std::list<Card*> &currentPlayerDeck, std::array<std::set<Card*, Players::lex_compare>, 4> &arrayOfSets, 
					std::list<Card*> &currentPlayerDiscards, int &theChosenOne, std::array<Players*, 4> &allPlayers, std::array<Card*, 52> myDeck); 
};

#endif