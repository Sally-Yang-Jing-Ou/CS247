#ifndef _GAMELOGIC_
#define _GAMELOGIC_

#include <iostream>
#include <list>
#include <set>
#include <vector>
#include "Player.h"
#include "Deck.h"
#include "Table.h"
#include "Card.h"
#include "Command.h"

class GameLogic {
public:
	GameLogic();
	~GameLogic();
	void invitePlayer(int playerChoice);
	Deck &deck();
	Table &table();
	int &theChosenOne ();
	void dealCards();
	bool gameOver();
	void beginGame();
	std::vector<int> winners() const;
private:
	static const int PLAYER_COUNT = 4;
	std::vector<Player*> allPlayer_; //keep track of all 4 players
	Deck deck_;
	Table table_;
	int theChosenOne_;
	int allPlayerScores_[4];
	bool firstTurn_;
	bool isLegalPlayInCommand (Card theCard);
	bool isLegalPlay (int itRank, int it2Rank, int itSuit, int it2Suit);
	void printLegalPlays (std::list<Card*> currentPlayerDeck);
	void printOptions (std::list<Card*> currentPlayerDeck);
	bool legalPlayInDeckExists (std::list<Card*> currentPlayerDeck, Table &table);
	void playTurn(Player * player, bool shouldDisplayOptions);
};

#endif
