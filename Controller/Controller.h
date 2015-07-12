#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/GameLogic.h"

class Controller {
public:
    Controller(GameLogic * gameLogic);
    ~Controller();
    void onPlayerOptionChosen(int playerType); //0 for human, 1 for computer

private:
    GameLogic * gameLogic_;
};

#endif
