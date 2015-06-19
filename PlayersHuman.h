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
    void playCard(Card card, int &theChosenOne);
    void discardCard(Card card, int &theChosenOne);
private: 

};

#endif
