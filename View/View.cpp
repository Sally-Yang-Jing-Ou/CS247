#include "view.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//constructor for popup dialog
View::PopupMessage::PopupMessage(Gtk::Window &main, string title, string message): Dialog( title, main, true, true ), msg(message, Gtk::ALIGN_LEFT) {
    Gtk::VBox* contentArea = this->get_vbox();
    contentArea->add(msg);

    Gtk::Button * closeButton = add_button( Gtk::Stock::CLOSE, Gtk::RESPONSE_CLOSE);
    show_all_children();

    run ();
}


View::View(Controller * controller, GameLogic * gameLogic) : gameLogic_(gameLogic), controller_(controller), container_(true, 10), handBox_(true, 10), startButton_("Start Game"), endButton_("End Game"), 
                                                            seedLabel_("Seed: "), cardTableView_(4, 13, true), menuBox_(true,2), table(4), progressLabel_("Progress in Game ") {
    set_title("Straights");

    seedField_.set_text("0");
    menuBox_.pack_start(startButton_, false, false);
    menuBox_.pack_start(seedLabel_, Gtk::PACK_SHRINK);
    menuBox_.pack_start(seedField_, Gtk::PACK_SHRINK);
    menuBox_.pack_start(progressLabel_, false, false);
    menuBox_.pack_start(progressBar_);
    menuBox_.pack_start(endButton_, false, false);
    startButton_.signal_clicked().connect( sigc::mem_fun( *this, &View::onStartButtonClicked ) );
    endButton_.signal_clicked().connect(sigc::mem_fun(*this, &View::onEndButtonClicked));

    //container_.pack_start(menuBox_);

    table.attach(menuBox_, 0, 1, 0, 1);

    cardFrame_.set_label("Table");
    cardFrame_.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    cardFrame_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    cardTableView_.set_col_spacings(1);
    cardTableView_.set_row_spacings(2);

    for(int i = ACE; i < 13; i++) {
        clubs_[i] = new Gtk::Image(deck_.null());
        cardTableView_.attach(*clubs_[i], i, i+1, 0, 1);
        diamonds_[i] = new Gtk::Image(deck_.null());
        cardTableView_.attach(*diamonds_[i], i, i+1, 1, 2);
        hearts_[i] = new Gtk::Image(deck_.null());
        cardTableView_.attach(*hearts_[i], i, i+1, 2, 3);
        spades_[i] = new Gtk::Image(deck_.null());
        cardTableView_.attach(*spades_[i], i, i+1, 3, 4);
    }

    cardFrame_.add(cardTableView_);

	handBoxFrame_.set_label( "Hand:" );
	handBoxFrame_.set_label_align( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
	handBoxFrame_.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
    //container_.pack_start(handBoxFrame_);

    for (int i = 0; i < 4; i++) {
        playerBox_[i].rageButton().signal_clicked().connect(sigc::mem_fun(*this, &View::onRageButtonClicked));
        stringstream number;
        number << (i+1);
        string currentPlayer = "Player " + number.str();
        playerBox_[i].set_label(currentPlayer);
        playerHBox_.add(playerBox_[i]);
    }

    //current hand
    for (int i = 0; i < 13; i++) {
        hand_[i] = new Gtk::Image(deck_.null());
        handButton_[i].set_image(*hand_[i]);
        handButton_[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &View::onCardClicked), i));
        handBox_.add(handButton_[i]);
    }

    handBoxFrame_.add( handBox_ );

    table.attach(playerHBox_, 0, 1, 2, 3);
    table.attach(cardFrame_, 0, 1, 1, 2);
    table.attach(handBoxFrame_, 0, 1, 3, 4);
    add(table);

    //add(container_);
    show_all();
    gameLogic_->subscribe(this);
}

void View::onStartButtonClicked() {
    //set seed
    string seed = seedField_.get_text();
    gameLogic_->setSeed(atoi(seed.c_str()));
    //remove current players if there are any
    controller_->removeCurrentPlayers();
    //invite players
    for (int i = 0; i < 4; i++) {
        Gtk::Dialog dialog( "Invite Players", *this );
        stringstream sstm;
        sstm << "Is player " << i+1 << " a human or computer player?";
        string promptText = sstm.str();
        Gtk::Label prompt(promptText);

        Gtk::VBox* contentArea = dialog.get_vbox();
        contentArea->pack_start(prompt, true, false);
        prompt.show();

        dialog.add_button("Human", 0);
        dialog.add_button("Computer", 1);

    	int result = dialog.run();
        controller_->onPlayerOptionChosen(result);
    }
    restart();
    gameLogic_->restartGame(false);
    controller_->onStartButtonClicked();
}

void View::update() {

    list<Card*> currentHand = gameLogic_->getHandForCurrentPlayer();
    int i = 0;
    for (std::list<Card*>::iterator it = currentHand.begin(); it != currentHand.end(); it++) {
        hand_[i]->set(deck_.image((*it)->getRank(), (*it)->getSuit()));
        i++;
    }

    while(i < 13) {
        hand_[i]->set(deck_.null());
        i++;
    }

    Card *mostRecentCard = gameLogic_->mostRecentCard();
    if(mostRecentCard != NULL) { //update table if a legal play was made
        if (mostRecentCard->getSuit() == CLUB){
            clubs_[mostRecentCard->getRank()]->set(deck_.image(mostRecentCard->getRank(), mostRecentCard->getSuit()));
        } else if (mostRecentCard->getSuit() == DIAMOND){
            diamonds_[mostRecentCard->getRank()]->set(deck_.image(mostRecentCard->getRank(), mostRecentCard->getSuit()));
        } else if (mostRecentCard->getSuit() == SPADE){
            spades_[mostRecentCard->getRank()]->set(deck_.image(mostRecentCard->getRank(), mostRecentCard->getSuit()));
        } else if (mostRecentCard->getSuit() == HEART){
            hearts_[mostRecentCard->getRank()]->set(deck_.image(mostRecentCard->getRank(), mostRecentCard->getSuit()));
        }
        progressBar_.set_fraction(progress_/progressMax_);
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
            playerBox_[i].discardsSetter(ss.str());
        }
        progressBar_.set_fraction(progress_/progressMax_);
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
            playerBox_[i].scoreSetter(scores.str());
        } 
        if (gameLogic_->gameOver()){
            PopupMessage dialog(*this, "Game Over", gameLogic_->winners());
            for (int i = 0; i < 4; i++){
                playerBox_[i].scoreSetter("0");
            } 
        }
        restart();
    }
}

void View::onEndButtonClicked() {
    for(int i = 0; i < 4; i++) {
        playerBox_[i].scoreSetter("0");
    }
    restart();
    controller_->onEndButtonClicked();
}

void View::onCardClicked(int index){
    try{
        controller_->onCardClicked(index);
     } catch (GameLogic::InvalidMoveException ex) {
        PopupMessage dialog(*this, "Invalid Move", ex.getMessage());
    }
}

void View::onRageButtonClicked(){
    controller_->onRageButtonClicked();
}

void View::restart() {
    for (int i = 0; i < 4; i++) {
        playerBox_[i].discardsSetter("0");
        playerBox_[i].activate(false);
    }

    for(int i = ACE; i < RANK_COUNT; i++) {
        clubs_[i]->set(deck_.null());
        diamonds_[i]->set(deck_.null());
        hearts_[i]->set(deck_.null());
        spades_[i]->set(deck_.null());
        hand_[i]->set(deck_.null());
    }
    progress_=0;
    progressBar_.set_fraction(progress_/progressMax_);
}

View::~View() {
    for(int i = 0; i < 13; i++) {     
        if(clubs_[i] != NULL) {
            delete clubs_[i];
        }
        if(diamonds_[i] != NULL) {
            delete diamonds_[i];
        }
        if(hearts_[i] != NULL) {
            delete hearts_[i];
        }
        if(spades_[i] != NULL) {
            delete spades_[i];
        }
        if(hand_[i] != NULL) {
            delete hand_[i];
        }
    }
}
