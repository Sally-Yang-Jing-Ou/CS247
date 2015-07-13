#ifndef _ComputerPlayer_
#define _ComputerPlayer_

#include <iostream>
#include <string>
#include <list>
#include "Player.h"
#include "../Card.h"
#include "../Command.h"
#include "Table.h"

class ComputerPlayer : public Player { //inherits from Player
public:
	ComputerPlayer();
	~ComputerPlayer();
    Card* firstLegalCardInDeck (Table &table, bool &firstTurn);
	ComputerPlayer( Player& copyPlayer );
    Card* makeMove(Table &table, bool &firstTurn, int &theChosenOne);
};

#endif