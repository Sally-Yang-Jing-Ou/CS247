#include <istream>
#include <list>
#include "Card.h"
#include "Players.h"

using namespace std;

Players::Players() {}

Players::~Players() {}

std::list<Card*> &Players::getDeck() {
	return playersDeck_;
}
