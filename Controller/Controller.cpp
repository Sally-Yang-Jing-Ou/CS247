#include "Controller.h"

using namespace std;

Controller::Controller(GameLogic * gameLogic, Log * log): gameLogic_(gameLogic), log_(log) {    
}

void Controller::onPlayerOptionChosen(int playerType) {
    gameLogic_->invitePlayer(playerType);
}

void Controller::onRageButtonClicked() {
	gameLogic_->ragequit();
}

void Controller::onStartButtonClicked() {
    log_->log("The game has been started.");
	gameLogic_->dealCards();
	gameLogic_->beginGame();
}

void Controller::onCardClicked(int index) {
	gameLogic_->playTurn(index);
}

void Controller::onEndButtonClicked() {
    log_->log("The game has been ended.");
	gameLogic_->restartGame();
}

void Controller::removeCurrentPlayers() {
	gameLogic_->removeCurrentPlayers();
}