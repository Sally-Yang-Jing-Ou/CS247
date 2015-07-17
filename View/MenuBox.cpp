#include "MenuBox.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

MenuBox::MenuBox(Controller * controller, GameLogic * gameLogic, View * window): HBox(true,2), gameLogic_(gameLogic), controller_(controller), startButton_("Start Game"), endButton_("End Game"), seedLabel_("Seed: "), progressLabel_("Progress in Game "), mainWindow_(window) {
    seedField_.set_text("0");
    
    pack_start(startButton_);
    pack_end(endButton_);
    pack_start(seedLabel_, Gtk::PACK_SHRINK);
    pack_start(seedField_);
    pack_end(progressBar_);
    pack_end(progressLabel_, Gtk::PACK_SHRINK);

    startButton_.signal_clicked().connect( sigc::mem_fun( *this, &MenuBox::onStartButtonClicked ) );
    endButton_.signal_clicked().connect(sigc::mem_fun(*this, &MenuBox::onEndButtonClicked));
}

MenuBox::~MenuBox() {}

void MenuBox::updateProgressBar(double increment) {
    progressBar_.set_fraction(increment);
}

void MenuBox::onStartButtonClicked() {
    //set seed
    string seed = seedField_.get_text();
    gameLogic_->setSeed(atoi(seed.c_str()));
    //remove current players if there are any
    controller_->removeCurrentPlayers();
    //invite players
    for (int i = 0; i < 4; i++) {
        Gtk::Dialog dialog( "Invite Players", *mainWindow_ );
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
    mainWindow_->restart();
    gameLogic_->restartGame(false);
    controller_->onStartButtonClicked();
}

void MenuBox::onEndButtonClicked() {
    for(int i = 0; i < 4; i++) {
        mainWindow_->getPlayerBox(i)->setScore("0");
    }
    mainWindow_->restart();
    controller_->onEndButtonClicked();
}