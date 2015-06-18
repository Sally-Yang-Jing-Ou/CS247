#ifndef _TABLE_
#define _TABLE_

#include <iostream>
#include <set>
#include <array>
#include <vector>
#include "Card.h"

class Table {
public:
	Table();
	~Table();
	void printTable();
    void placeCard (Card *card);
    void placeCardsOnTable (std::vector<Card*> &vectorOfCard, Card *card);
	std::array< std::vector<Card*>, 4> &returnArrayOfSets();
	std::vector<Card*> &returnVectorOfClubs();
	std::vector<Card*> &returnVectorOfDiamonds();
	std::vector<Card*> &returnVectorOfHearts();
	std::vector<Card*> &returnVectorOfSpades();

private:
	std::array< std::vector<Card*>, 4> arrayOfSets_;
	std::vector<Card*> vectorOfClubs_;
	std::vector<Card*> vectorOfDiamonds_;
	std::vector<Card*> vectorOfHearts_;
	std::vector<Card*> vectorOfSpades_;
};

#endif

