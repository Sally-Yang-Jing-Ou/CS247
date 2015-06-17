#ifndef _TABLE_
#define _TABLE_

#include <iostream>
#include <set>
#include <array>
#include "Card.h"
#include "Players.h"

class Table {
public:
	Table();
	~Table();
	void printTable();
	std::array< std::set<Card*, Players::lex_compare>, 4> &returnArrayOfSets();
	std::set<Card*, Players::lex_compare> &returnSetOfClubs();
	std::set<Card*, Players::lex_compare> &returnSetOfDiamonds();
	std::set<Card*, Players::lex_compare> &returnSetOfHearts();
	std::set<Card*, Players::lex_compare> &returnSetOfSpades();

private:
	std::array< std::set<Card*, Players::lex_compare>, 4> arrayOfSets_;
	std::set<Card*, Players::lex_compare> setOfClubs_;
	std::set<Card*, Players::lex_compare> setOfDiamonds_;
	std::set<Card*, Players::lex_compare> setOfHearts_;
	std::set<Card*, Players::lex_compare> setOfSpades_;
};

#endif

