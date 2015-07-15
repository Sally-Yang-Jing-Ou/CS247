#ifndef _HumanPlayer_
#define _HumanPlayer_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Player.h"
#include "../Card.h"
#include "../Command.h"
#include "Table.h"
#include "Log.h"


class HumanPlayer : public Player { //inherits from Player
public:
	HumanPlayer(Log * log);
	~HumanPlayer();
private: 

};

#endif
