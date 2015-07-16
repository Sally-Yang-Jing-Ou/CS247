#ifndef _HumanPlayer_
#define _HumanPlayer_

#include "Player.h"
#include "Log.h"


class HumanPlayer : public Player { //inherits from Player
public:
	HumanPlayer(Log * log);
	~HumanPlayer();
private: 

};

#endif
