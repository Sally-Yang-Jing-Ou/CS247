#include "Table.h"
#include <cassert>
#include <algorithm>

using namespace std;	

Table::Table() : arrayOfSets_(new vector<vector<Card*>* >()) {
    for (int i = 0; i < 4; i++) {
        arrayOfSets_->push_back(new vector<Card*>());
    }
};
Table::~Table() {
    for (int i = 0; i < 4; i++) {
        delete arrayOfSets_->at(i);
    }
    delete arrayOfSets_;
};

vector<vector<Card*>* >* Table::returnArrayOfSets() {
	return arrayOfSets_;
}

void Table::placeCard(Card *card) {
    arrayOfSets_->at(card->getSuit())->push_back(card);
}

void Table::clearTable() {
    for (int i = 0; i < 4; i++) {
        arrayOfSets_->at(i)->clear();
    }
}

bool lessThan(const Card *lhs, const Card *rhs)
{
    return lhs->getRank( ) < rhs->getRank( );
}

void Table::printTable() {
	cout << "Cards on the table:" << endl;
	cout << "Clubs:";
	vector<vector<Card*>* >* arrayOfSets = returnArrayOfSets();
	for (int i = 0; i < 4; i ++) {
		vector<Card*>* setOfSuit = arrayOfSets->at(i);
		if (i==1) cout << "Diamonds:";
		else if (i==2) cout << "Hearts:";
		else if (i==3) cout << "Spades:";
		if (!setOfSuit->empty()) {
			sort(setOfSuit->begin(), setOfSuit->end(), lessThan);
			for (std::vector<Card*>::iterator it = setOfSuit->begin(); it != setOfSuit->end(); it++) {
				cout << " " << ((*it)->getRankInString());
			}
			cout << endl;
		} else {
			cout << "" << endl;
		}
	}
}