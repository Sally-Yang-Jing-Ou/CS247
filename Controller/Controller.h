#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/GameLogic.h"
#include "../Model/Log.h"

class Controller {
public:
    Controller(GameLogic * gameLogic, Log * log);
    void onPlayerOptionChosen(int playerType); //handles when user selects whether a player is human/computer
    void onRageButtonClicked(); //handles when the ragequit button is clicked
    void onStartButtonClicked(); //handles when the start button is clicked
    void onCardClicked(int index); //handles when a card is clicked
    void onEndButtonClicked(); //handles when the end button is clicked
    void removeCurrentPlayers(); //cleans up current players

private:
    GameLogic * gameLogic_;
    Log * log_;
};

#endif
