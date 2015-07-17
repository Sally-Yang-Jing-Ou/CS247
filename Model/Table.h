#ifndef _TABLE_
#define _TABLE_

#include <iostream>
#include <set>
#include <vector>
#include "../Card.h"
#include "Subject.h"

class Table {
public:
	Table(); //constructor
	~Table(); //destructor
	void printTable(); //outputs table to console
    void placeCard (Card *card); //places card in the table
    void clearTable(); //clears the table
	std::vector<std::vector<Card*>* >* returnArrayOfSets(); //returns all cards on table

private:
	std::vector<std::vector<Card*>* >* arrayOfSets_; //ADT that holds all cards on table
};

#endif
