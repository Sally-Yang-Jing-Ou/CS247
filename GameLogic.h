#ifndef _GAMELOGIC_
#define _GAMELOGIC_

#include <iostream>
#include <list>
#include <set>
#include <vector>
#include "Players.h"
#include "Deck.h"
#include "Table.h"
#include "Card.h"
#include "Command.h"

class GameLogic {
public:
	GameLogic();
	~GameLogic();
	void invitePlayers(char playerChoice, int i); 
	Deck &deck();
	Table &table();
	int &theChosenOne ();
	void dealCards();
	bool gameOver();
	void beginGame();
	std::vector<int> winners() const;

private:
	static const int PLAYER_COUNT = 4;
	std::vector<Players*> allPlayers_; //keep track of all 4 players
	Deck deck_;
	Table table_;
	int theChosenOne_;
	int allPlayersScores_[4];

};

#endif