#include "PlayersHuman.h"
#include <cassert>

using namespace std;

bool printed = false;

PlayersHuman::PlayersHuman() {}

PlayersHuman::~PlayersHuman() {}

bool isLegal (int itRank, int it2Rank, int itSuit, int it2Suit) {
	if (itRank == 7 || 
	(itRank -1 == it2Rank && itSuit == it2Suit) ||
	(itRank +1 == it2Rank && itSuit == it2Suit)) {
		return true;
	}
	return false;
}

void printLegalPlays (std::list<Card*> currentPlayerDeck, array<set<Card*, Players::lex_compare>, 4> arrayOfSets) {
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		printed = false;
		for (int i = 0; i < 4; i ++) {
			set<Card*, Players::lex_compare> setOfSuit = arrayOfSets[i];
			if (!setOfSuit.empty() && !printed) {
				for (std::set<Card*, Players::lex_compare>::iterator it2 = setOfSuit.begin(); it2 != setOfSuit.end(); it2++) {
					if (isLegal((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
						cout << " " << (**it);
						printed = true;
						break;
					}
				}
			}
		}
	}
}

void PlayersHuman::PrintOutTable (std::list<Card*> currentPlayerDeck, array<set<Card*, Players::lex_compare>, 4> arrayOfSets) {
	cout << "Card on the table:" << endl;
	cout << "Clubs:";
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
	cout << "Your hand:";
	if (!currentPlayerDeck.empty()) {
		for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
			cout << " " << (**it);
		}
		cout << endl;
	} else {
		cout << "" << endl;
	}

	cout << "Legal Plays:";
	if (!currentPlayerDeck.empty()) {
		printLegalPlays(currentPlayerDeck, arrayOfSets);
		cout << endl;
	} else {
		cout << "" << endl;
	}
}