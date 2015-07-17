#ifndef _ComputerPlayer_
#define _ComputerPlayer_

#include <iostream>
#include <string>
#include <list>
#include "Player.h"
#include "../Card.h"
#include "Table.h"
#include "Log.h"

class ComputerPlayer : public Player { //inherits from Player
public:
	ComputerPlayer(Log * log); //constructor
	~ComputerPlayer(); //destructor
    Card* firstLegalCardInDeck (Table &table, bool &firstTurn); //returns the first legal card in player's hand
	ComputerPlayer( Player& copyPlayer ); //copy constructor
    Card* makeMove(Table &table, bool &firstTurn, int &theChosenOne); //computer plays a turn
};

#endif