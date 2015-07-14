#ifndef _GAMELOGIC_
#define _GAMELOGIC_

#include <iostream>
#include <list>
#include <set>
#include <vector>
#include "Player.h"
#include "Deck.h"
#include "Table.h"
#include "../Card.h"
#include "../Command.h"
#include "../View/Observer.h"
#include "Subject.h"

class GameLogic: public Subject {
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
	std::string winners() const;
	void setSeed(int seed);
	Card* mostRecentCard() const;		
	std::list<Card*> getHandForCurrentPlayer();
	bool isRoundFinished();
	std::string roundStats();
	void restartGame(bool resetAll = true);	
	void ragequit();
	std::vector<int> discardsAmount() const;
	void playTurn(int index);
	int* allPlayerScores (); 
	class InvalidMoveException{
    private:
        std::string message;
    public:
        InvalidMoveException(std::string);
        std::string getMessage(){return message;}
    };
    void removeCurrentPlayers();

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
	Card *mostRecentCard_;
	bool isRoundFinished_;
	std::string roundStats_;

};

#endif
