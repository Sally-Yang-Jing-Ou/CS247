#include "view.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

View::View(Controller * controller, GameLogic * gameLogic, Log * log) : gameLogic_(gameLogic), controller_(controller), menuBox_(new MenuBox(controller, gameLogic, this)), handBox_(new HandBox(controller, gameLogic, this, &deck_)), cardTable_(new CardTable(controller, gameLogic, &deck_)), logger_(new Logger(controller, gameLogic, log)), table(4,2,false) {
    set_title("Straights");

    for (int i = 0; i < 4; i++) {
        playerBox_[i].rageButton().signal_clicked().connect(sigc::mem_fun(*this, &View::onRageButtonClicked));
        stringstream number;
        number << (i+1);
        string currentPlayer = "Player " + number.str();
        playerBox_[i].set_label(currentPlayer);
        playerHBox_.add(playerBox_[i]);
    }

    table.attach(*menuBox_, 0, 1, 0, 1);
    table.attach(*cardTable_, 0, 1, 1, 2);
    table.attach(playerHBox_, 0, 1, 2, 3);
    table.attach(*handBox_, 0, 1, 3, 4);
    table.attach(*logger_, 1, 2, 0, 4);

    add(table);

    show_all();
    gameLogic_->subscribe(this);
}

PlayerBox * View::getPlayerBox(int index) {
    return &playerBox_[index];
}

void View::update() {
    handBox_->update();

    Card *mostRecentCard = gameLogic_->mostRecentCard();
    if(mostRecentCard != NULL) { //update table if a legal play was made
        cardTable_->update();
        
        menuBox_->updateProgressBar(progress_/progressMax_);
        while(Gtk::Main::instance()->events_pending()){
            Gtk::Main::instance()->iteration();
        }
        if(progress_<progressMax_){
            progress_++;
        }
    } else { //update discards number
        vector<int> discards = gameLogic_->discardsAmount();
        for(int i = 0; i < 4; i++) {
            stringstream ss;
            ss << discards[i];
            playerBox_[i].setDiscards(ss.str());
        }
    
        menuBox_->updateProgressBar(progress_/progressMax_);
        while(Gtk::Main::instance()->events_pending()){
            Gtk::Main::instance()->iteration();
        }
        if(progress_<progressMax_){
            progress_++;
        }
    }

    //highlight current player, de-highlight others
    int theChosenOne = gameLogic_->theChosenOne();
    for(int i = 0; i < 4; i++) {
        playerBox_[i].activate(false);  //set_sensitive
        if (i == theChosenOne){
            playerBox_[i].activate(true);
        }
    }

    if (gameLogic_->isRoundFinished()) {
        PopupMessage dialog(*this, "Round Finished", gameLogic_->roundStats());
        int* allPlayerScores = gameLogic_ ->allPlayerScores();
        for (int i = 0; i < 4; i++){
            stringstream scores;
            scores << allPlayerScores[i];
            playerBox_[i].setScore(scores.str());
        } 
        if (gameLogic_->gameOver()){
            PopupMessage dialog(*this, "Game Over", gameLogic_->winners());
            for (int i = 0; i < 4; i++){
                playerBox_[i].setScore("0");
            } 
        }
        restart();
    }
}

void View::onRageButtonClicked(){
    controller_->onRageButtonClicked();
}

void View::restart() {
    for (int i = 0; i < 4; i++) {
        playerBox_[i].setDiscards("0");
        playerBox_[i].activate(false);
    }

    for(int i = ACE; i < RANK_COUNT; i++) {
        handBox_->setHand(i, deck_.null());
    }
    cardTable_->prepareForRestart();

    progress_=0;
    menuBox_->updateProgressBar(progress_/progressMax_);
}

View::~View() {
    delete menuBox_;
    delete handBox_;
    delete cardTable_;
}
