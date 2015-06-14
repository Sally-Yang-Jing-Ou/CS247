#include <istream>
#include <list>
#include "Card.h"
#include "PlayersComputer.h"

using namespace std;

PlayersComputer::PlayersComputer() {}

PlayersComputer::~PlayersComputer() {}

PlayersComputer::PlayersComputer( Players& copyPlayer1 ):Players(copyPlayer1) {}

void PlayersComputer::PrintOutTable (std::list<Card*> currentPlayerDeck, std::array<std::set<Card*, Players::lex_compare>, 4> arrayOfSets) {

}