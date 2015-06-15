#ifndef _PLAYERSHUMAN_
#define _PLAYERSHUMAN_

#include <iostream>
#include <string>
#include <list>
#include <array>
#include <set>
#include "Players.h"
#include "Card.h"
#include "Command.h"

class PlayersHuman : public Players { //inherits from Players
public:
	PlayersHuman();
	~PlayersHuman();
	void DoAction (bool &firstTurn, std::list<Card*> &currentPlayerDeck, std::array<std::set<Card*, lex_compare>, 4> &arrayOfSets, 
					std::list<Card*> &currentPlayerDiscards, int &theChosenOne, std::array<Players*, 4> &allPlayers, std::array<Card*, 52> myDeck); 

private: 

};

#endif