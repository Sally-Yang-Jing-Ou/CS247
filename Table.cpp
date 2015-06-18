#include "Table.h"
#include <cassert>
#include <algorithm>

using namespace std;	

Table::Table() {};
Table::~Table() {};

array< vector<Card*>, 4> &Table::returnArrayOfSets() {
	arrayOfSets_[0] = returnVectorOfClubs();
	arrayOfSets_[1] = returnVectorOfDiamonds();
	arrayOfSets_[2] = returnVectorOfHearts();
	arrayOfSets_[3] = returnVectorOfSpades();
	return arrayOfSets_;
}

vector<Card*> &Table::returnVectorOfClubs() {
	return vectorOfClubs_;
}

vector<Card*> &Table::returnVectorOfDiamonds() {
	return vectorOfDiamonds_;
}

vector<Card*> &Table::returnVectorOfHearts() {
	return vectorOfHearts_;
}

vector<Card*> &Table::returnVectorOfSpades() {
	return vectorOfSpades_;
}

void Table::placeCardsOnTable (vector<Card*> &vectorOfCard, Card *card) {
    vectorOfCard.push_back(card);
}

void Table::placeCard(Card *card) {
	
	switch(card->getSuit()) {
		case CLUB:
			placeCardsOnTable(vectorOfClubs_, card);
			break;
		case DIAMOND:
			placeCardsOnTable(vectorOfDiamonds_, card);
			break;
		case HEART:
			placeCardsOnTable(vectorOfHearts_, card);
			break;
		case SPADE:
			placeCardsOnTable(vectorOfSpades_, card);
			break;
		default:
			break;
	}
}

bool lessThan(const Card *lhs, const Card *rhs)
{
    return lhs->getRank( ) < rhs->getRank( );
}

void Table::printTable() {
	cout << "Card on the table:" << endl;
	cout << "Clubs:";
	array< vector<Card*>, 4> arrayOfSets = returnArrayOfSets();
	for (int i = 0; i < 4; i ++) {
		vector<Card*> setOfSuit = arrayOfSets[i];
		if (i==1) cout << "Diamonds:";
		else if (i==2) cout << "Hearts:";
		else if (i==3) cout << "Spades:";
		if (!setOfSuit.empty()) {
			sort(setOfSuit.begin(), setOfSuit.end(), lessThan);
			for (std::vector<Card*>::iterator it = setOfSuit.begin(); it != setOfSuit.end(); it++) {
				cout << " " << ((*it)->getRankInString());
			}
			cout << endl;
		} else {
			cout << "" << endl;
		}
	}
}