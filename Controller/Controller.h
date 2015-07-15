#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/GameLogic.h"
#include "../Model/Log.h"

class Controller {
public:
    Controller(GameLogic * gameLogic, Log * log);
    void onPlayerOptionChosen(int playerType); //0 for human, 1 for computer
    void onRageButtonClicked();
    void onStartButtonClicked();
    void onCardClicked(int index);
    void onEndButtonClicked();
    void removeCurrentPlayers();

private:
    GameLogic * gameLogic_;
    Log * log_;
};

#endif
