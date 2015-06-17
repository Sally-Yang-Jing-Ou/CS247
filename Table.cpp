#include "Table.h"
#include <cassert>

using namespace std;	

Table::Table() {};
Table::~Table() {};

array< set<Card*, Players::lex_compare>, 4> &Table::returnArrayOfSets() {
	arrayOfSets_[0] = returnSetOfClubs();
	arrayOfSets_[1] = returnSetOfDiamonds();
	arrayOfSets_[2] = returnSetOfHearts();
	arrayOfSets_[3] = returnSetOfSpades();
	return arrayOfSets_;
}

set<Card*, Players::lex_compare> &Table::returnSetOfClubs() {
	return setOfClubs_;
}

set<Card*, Players::lex_compare> &Table::returnSetOfDiamonds() {
	return setOfDiamonds_;
}

set<Card*, Players::lex_compare> &Table::returnSetOfHearts() {
	return setOfHearts_;
}

set<Card*, Players::lex_compare> &Table::returnSetOfSpades() {
	return setOfSpades_;
}

void Table::printTable() {
	cout << "Card on the table:" << endl;
	cout << "Clubs:";
	array< set<Card*, Players::lex_compare>, 4> arrayOfSets = returnArrayOfSets();
	for (int i = 0; i < 4; i ++) {
		set<Card*, Players::lex_compare> setOfSuit = arrayOfSets[i];
		if (i==1) cout << "Diamonds:";
		else if (i==2) cout << "Hearts:";
		else if (i==3) cout << "Spades:";
		if (!setOfSuit.empty()) {
			for (std::set<Card*, Players::lex_compare>::iterator it = setOfSuit.begin(); it != setOfSuit.end(); it++) {
				cout << " " << ((*it)->getRankInString());
			}
			cout << endl;
		} else {
			cout << "" << endl;
		}
	}
}