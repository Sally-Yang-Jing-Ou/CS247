#ifndef _Player_
#define _Player_

#include <iostream>
#include <list>
#include <vector>
#include "Card.h"
#include "Command.h"
#include "Table.h"

class Player {
public:
	Player();// constructor
    virtual ~Player();  // destructor
    Player( Player& copyPlayer );  // copy constructor
    std::list<Card*> &getDeck(); //getter for player's deck
    std::list<Card*> &getDiscards(); //getter for the discards
    int &getOldScore();
    void setNewScore();
    bool isDeckEmpty();
    int scoreGained();
    void roundEndsMessage(int i);
    void eraseCardFromHand (Card *card);
    void addCardToDiscards (Card *card);
    void playCard(Card card, Table &table, int &theChosenOne);
    void discardCard(Card card, Table &table, int &theChosenOne);
private:
	std::list<Card*> PlayerDeck_; //each player's deck of cards
	std::list<Card*> PlayerDiscards_; //each player's deck of discards
	int oldScore_;

};

#endif
