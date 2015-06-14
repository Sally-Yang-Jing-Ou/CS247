#ifndef _PLAYERSHUMAN_
#define _PLAYERSHUMAN_

#include <iostream>
#include <string>
#include <list>
#include <array>
#include <set>
#include "Players.h"
#include "Card.h"

class PlayersHuman : public Players { //inherits from Players
public:
	PlayersHuman();
	~PlayersHuman();
	void PrintOutTable (std::list<Card*> currentPlayerDeck, std::array<std::set<Card*, Players::lex_compare>, 4> arrayOfSets);

private: 

};

#endif