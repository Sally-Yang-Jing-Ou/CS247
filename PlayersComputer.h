#ifndef _PLAYERSCOMPUTER_
#define _PLAYERSCOMPUTER_

#include <iostream>
#include <string>
#include <list>
#include "Players.h"
#include "Card.h"
#include "Command.h"
#include "Table.h"

class PlayersComputer : public Players { //inherits from Players
public:
	PlayersComputer();
	~PlayersComputer();
    Card* firstLegalCardInDeck (Table &table, bool &firstTurn);
	PlayersComputer( Players& copyPlayer );
    void doAction (Table &table, bool &firstTurn, int theChosenOne, std::vector<Players*> &allPlayers, std::vector<Card*> &myDeck);
};

#endif