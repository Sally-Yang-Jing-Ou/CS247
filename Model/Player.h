#ifndef _Player_
#define _Player_

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "../Card.h"
#include "Table.h"
#include "Subject.h"
#include "Log.h"

class Player {
public:
    Player(Log * log);// constructor
    virtual ~Player();  // destructor
    Player( Player& copyPlayer );  // copy constructor
    std::list<Card*> &getDeck(); //getter for player's deck
    std::list<Card*> &getDiscards(); //getter for the discards
    int &getOldScore(); //getter for old score
    void setNewScore(); //setter for new score
    bool isDeckEmpty(); //checks if the deck is empty
    int scoreGained(); //gets the score gained
    std::string roundEndsMessage(int i); //gets the round ends message
    void eraseCardFromHand (Card *card); //removes card from hand
    void addCardToDiscards (Card *card); //adds card to discards
    Card* playCard(Card card, Table &table, int &theChosenOne); //plays a card
    Card* discardCard(Card card, Table &table, int &theChosenOne); //discards a card
    void addCardToHand(Card* card); //adds a card to player's hand

private:
    std::list<Card*> PlayerDeck_; //each player's deck of cards
    std::list<Card*> PlayerDiscards_; //each player's deck of discards
    int oldScore_; //the player's old score
    Log * log_; //reference to log
};

#endif
