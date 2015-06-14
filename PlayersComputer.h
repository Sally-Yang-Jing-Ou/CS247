#ifndef _PLAYERSCOMPUTER_
#define _PLAYERSCOMPUTER_

#include <istream>
#include <string>
#include <list>
#include <array>
#include <set>
#include "Players.h"
#include "Card.h"

class PlayersComputer : public Players { //inherits from Players
public:
	PlayersComputer();
	~PlayersComputer();
	void PrintOutTable (std::list<Card*> currentPlayerDeck, std::array<std::set<Card*, Players::lex_compare>, 4> arrayOfSets);

private:
};

#endif