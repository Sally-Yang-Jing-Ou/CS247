#ifndef _GAMELOGIC_
#define _GAMELOGIC_

#include <iostream>
#include <list>
#include <array>
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
	std::array<Players*, PLAYER_COUNT> allPlayers_; //keep track of all 4 players
	Deck deck_;
	Table table_;
	int theChosenOne_;
	int allPlayersScores_[4];	
	bool firstTurn_;
	bool isLegalPlayInCommandHelper (Card theCard);
	bool isLegalPlayHelper (int itRank, int it2Rank, int itSuit, int it2Suit);
	void printLegalPlaysHelper (std::list<Card*> currentPlayerDeck, Table &table);
	void printOptions (Table &table, std::list<Card*> currentPlayerDeck);
	bool legalPlayInDeckExists (std::list<Card*> currentPlayerDeck, Table &table);
	void playTurn(Players * player);
};

#endif