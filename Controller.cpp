#include "Controller.h"

using namespace std;

Controller::Controller(GameLogic * gameLogic): gameLogic_(gameLogic)  {

}

Controller::~Controller() {
    
}

void Controller::onPlayerOptionChosen(int playerType) {
    gameLogic_->invitePlayer(playerType);
}
