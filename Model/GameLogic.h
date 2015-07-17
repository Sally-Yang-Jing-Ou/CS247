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
#include "../View/Observer.h"
#include "Subject.h"
#include "Log.h"

class GameLogic: public Subject {
public:
	GameLogic(Log * log); //constructor
	~GameLogic(); //destructor
	void invitePlayer(int playerChoice); //invites player of computer/human
	Deck &deck(); //returns deck reference
	Table &table(); //returns table reference
	int &theChosenOne (); //return current player reference
	void dealCards(); //deal cards to players
	bool gameOver(); //check if game is over
	void beginGame(); //begin the game
	std::string winners() const; //output winners string
	void setSeed(int seed); //setter for seed
	Card* mostRecentCard() const; //returns reference to the most recent card
	std::list<Card*> getHandForCurrentPlayer(); //returns list of the current player's hand
	bool isRoundFinished(); //checks if the round is over
	std::string roundStats(); //outputs the scores for a round
	void restartGame(bool resetAll = true);	 //restarts the game
	void ragequit(); //turns the current player into a computer player
	std::vector<int> discardsAmount() const; //returns a reference to the discard amounts
	void playTurn(int index); //high level function that plays a turn
	int* allPlayerScores (); //returns a pointer to the player scores
	bool isCardLegal(Card cardToCheck);  //checks if a card is legal
	class InvalidMoveException{ // custom exception class thrown when an illegal move is attempted to be performed
    private:
        std::string message;
    public:
        InvalidMoveException(std::string);
        std::string getMessage(){return message;}
    };
    void removeCurrentPlayers(); //cleans up current players

private:
	static const int PLAYER_COUNT = 4; //player count constant
	std::vector<Player*> allPlayer_; //keep track of all 4 players
	Deck deck_; //reference to deck
	Table table_; //reference to table
	int theChosenOne_; //reference to chosen player
	int allPlayerScores_[4]; //array of player scores
	bool firstTurn_; //flag for whether it's the first turn of the game
	bool isLegalPlayInCommand (Card theCard, bool ghost); //if ghost is true, stop side effects from happening
	bool isLegalPlay (int itRank, int it2Rank, int itSuit, int it2Suit); //checks whether a play is legal
	bool legalPlayInDeckExists (std::list<Card*> currentPlayerDeck, Table &table); //checks whether a legal play exists in a player's hand
	Card *mostRecentCard_; //reference to most recent card
	bool isRoundFinished_; //checks whether round is finished helper
	std::string roundStats_; //private reference to round stats
	Log * log_; //reference to log
};

#endif
