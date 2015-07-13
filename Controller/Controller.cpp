#include "Controller.h"

using namespace std;

Controller::Controller(GameLogic * gameLogic): gameLogic_(gameLogic)  {

}

void Controller::onPlayerOptionChosen(int playerType) {
    gameLogic_->invitePlayer(playerType);

}

void Controller::onRageButtonClicked() {
	gameLogic_->ragequit();
}

void Controller::onStartButtonClicked() {
	gameLogic_->dealCards();
	gameLogic_->beginGame();
}

void Controller::onCardClicked(int index) {
	gameLogic_->playTurn(index);
}

void Controller::onEndButtonClicked() {
	gameLogic_->restartGame();
}