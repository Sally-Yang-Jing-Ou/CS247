#ifndef _PLAYERSHUMAN_
#define _PLAYERSHUMAN_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Players.h"
#include "Card.h"
#include "Command.h"
#include "Table.h"


class PlayersHuman : public Players { //inherits from Players
public:
	PlayersHuman();
	~PlayersHuman();
    void printOutTable (Table &table, bool firstTurn);
    void doActionPlay ( Command &command, Table &table, bool &firstTurn, int theChosenOne);
    void doActionDiscard ( Table &table, int theChosenOne, Command &command);
    void doAction (Table &table, bool &firstTurn, int theChosenOne, std::vector<Players*> &allPlayers, std::vector<Card*> &myDeck);

private: 

};

#endif