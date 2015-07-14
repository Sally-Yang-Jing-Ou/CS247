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

//#define checkRep returnArrayOfSets

vector<vector<Card*>* >* Table::returnArrayOfSets() {
	// assert(arrayOfSets_);
	// for (int i = 0; i < arrayOfSets_->size(); ++i)
	// 	for (int j = 0; j < arrayOfSets_->at(i)->size(); ++j) {
	// 		const Card *c = arrayOfSets_->at(i)->at(j);
	// 		assert(c);
	// 		int r = (int)c->getRank(), s = (int)c->getSuit();
	// 		assert(0 <= r && r < 13);
	// 		assert(0 <= s && s < 4);
	// 	}
	return arrayOfSets_;
}

void Table::placeCard(Card *card) {
    //checkRep();
    arrayOfSets_->at(card->getSuit())->push_back(card);
    //checkRep();
}

void Table::clearTable() {
    //checkRep();
    for (int i = 0; i < 4; i++) {
        arrayOfSets_->at(i)->clear();
    }
    //checkRep();
}

bool lessThan(const Card *lhs, const Card *rhs)
{
    return lhs->getRank( ) < rhs->getRank( );
}

void Table::printTable() {
    //checkRep();
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
    //checkRep();
}
