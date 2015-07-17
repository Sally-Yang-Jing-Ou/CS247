#ifndef VIEW_H
#define VIEW_H

#include <gtkmm.h>
#include <gdkmm.h>
#include <list>
#include "DeckGUI.h"
#include "../Model/GameLogic.h"
#include "../Model/Log.h"
#include "../Controller/Controller.h"
#include "Observer.h"
#include "../Card.h"
#include "PlayerBox.h"
#include "MenuBox.h"
#include "HandBox.h"
#include "PopupMessage.h"
#include "CardTable.h"
#include "Logger.h"

class MenuBox;
class HandBox;

class View : public Gtk::Window, public Observer {
public:
        View(Controller * controller, GameLogic * gameLogic, Log * log); // where gameLogic is the common interface using facade pattern
        virtual ~View(); //destructor
        virtual void update(); //updates view
        void restart(); //restarts game/resets view
        PlayerBox * getPlayerBox(int index); //getter for PlayerBox

private:
        GameLogic * gameLogic_; //game logic is the model
        Controller * controller_; //controller

        Gtk::Table table; //top level container

        DeckGUI deck_; //allows access to images

        MenuBox * menuBox_; //inherits from HBox
        HandBox * handBox_; //inherits from Frame
        CardTable * cardTable_; //inherits from Frame
        Logger * logger_; //inherits from Frame

        PlayerBox playerBox_[4]; //player stats and view
        Gtk::HBox playerHBox_; //container for player boxes

        static const int progressMax_ = 52;
        int progress_ ;

        void onRageButtonClicked(); //handler for clicking rage button
};

#endif