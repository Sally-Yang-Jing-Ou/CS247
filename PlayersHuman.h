#ifndef _PLAYERSHUMAN_
#define _PLAYERSHUMAN_

#include <iostream>
#include <string>
#include <list>
#include <array>
#include <vector>
#include "Players.h"
#include "Card.h"
#include "Command.h"
#include "Table.h"


class PlayersHuman : public Players { //inherits from Players
public:
	PlayersHuman();
	~PlayersHuman();
    void DoActionPlay ( Command &command, Table &table, bool &firstTurn, std::list<Card*> &currentPlayerDeck, int &theChosenOne);
    void DoActionDiscard (std::list<Card*> &currentPlayerDeck, Table &table, std::list<Card*> &currentPlayerDiscards, int &theChosenOne, Command &command);
	void DoAction (Table &table, bool &firstTurn, std::list<Card*> &currentPlayerDeck,
					std::list<Card*> &currentPlayerDiscards, int &theChosenOne, std::array<Players*, 4> &allPlayers, std::array<Card*, 52> myDeck); 

    void playCard(Card card, int &theChosenOne);
    void discardCard(Card card, int &theChosenOne);
private: 

};

#endif