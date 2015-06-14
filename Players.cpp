#include <istream>
#include <list>
#include "Card.h"
#include "Players.h"

using namespace std;

Players::Players() {}

Players::~Players() {
	playersDeck_.clear();
	playersDiscards_.clear();
}

Players::Players( Players& copyPlayer ) {
	playersDeck_ = copyPlayer.getDeck();
	playersDiscards_ = copyPlayer.getDiscards();
}

std::list<Card*> &Players::getDeck() {
	return playersDeck_;
}

std::list<Card*> &Players::getDiscards() {
	return playersDiscards_;
}
