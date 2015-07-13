#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/GameLogic.h"

class Controller {
public:
    Controller(GameLogic * gameLogic);
    void onPlayerOptionChosen(int playerType); //0 for human, 1 for computer
    void onRageButtonClicked();
    void onStartButtonClicked();
    void onCardClicked(int index);
    void onEndButtonClicked();

private:
    GameLogic * gameLogic_;
};

#endif
