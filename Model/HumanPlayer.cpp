#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <cassert>
#include <cstdlib>

using namespace std;

bool printed = false;

HumanPlayer::HumanPlayer(Log * log): Player(log) {}

HumanPlayer::~HumanPlayer() {}
