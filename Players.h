#ifndef _PLAYERS_
#define _PLAYERS_

#include <istream>
#include <list>
#include <array>
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
    
	virtual void DoAction (Table &table, bool &firstTurn, std::list<Card*> &currentPlayerDeck,
					std::list<Card*> &currentPlayerDiscards, int &theChosenOne, std::array<Players*, 4> &allPlayers, std::array<Card*, 52> myDeck) = 0; 

private: 
	std::list<Card*> playersDeck_; //each player's deck of cards
	std::list<Card*> playersDiscards_; //each player's deck of discards
	int oldScore_;

};

#endif