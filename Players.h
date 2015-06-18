#ifndef _PLAYERS_
#define _PLAYERS_

#include <iostream>
#include <list>
#include <vector>
#include "Card.h"
#include "Command.h"
#include "Table.h"

class Players {
public: 
	Players();// constructor
    virtual ~Players();  // destructor
    Players( Players& copyPlayer );  // copy constructor
    std::list<Card*> &getDeck(); //getter for player's deck
    std::list<Card*> &getDiscards(); //getter for the discards
    int &getOldScore();
    void setNewScore();
    bool isDeckEmpty();
    int scoreGained();
    void roundEndsMessage(int i);
    void eraseCardFromHand (Card *card);
    void addCardToDiscards (Card *card);
    
	virtual void doAction (Table &table, bool &firstTurn, int theChosenOne, std::vector<Players*> &allPlayers, std::vector<Card*> &myDeck) = 0;

private: 
	std::list<Card*> playersDeck_; //each player's deck of cards
	std::list<Card*> playersDiscards_; //each player's deck of discards
	int oldScore_;

};

#endif