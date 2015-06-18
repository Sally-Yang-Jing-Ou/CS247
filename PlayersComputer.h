#ifndef _PLAYERSCOMPUTER_
#define _PLAYERSCOMPUTER_

#include <iostream>
#include <string>
#include <list>
#include <array>
#include "Players.h"
#include "Card.h"
#include "Command.h"
#include "Table.h"

class PlayersComputer : public Players { //inherits from Players
public:
	PlayersComputer();
	~PlayersComputer();
	PlayersComputer( Players& copyPlayer );
	void DoAction (Table &table, bool &firstTurn, std::list<Card*> &currentPlayerDeck,
					std::list<Card*> &currentPlayerDiscards, int &theChosenOne, std::array<Players*, 4> &allPlayers, std::array<Card*, 52> myDeck); 
};

#endif