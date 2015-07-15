#ifndef VIEW_H
#define VIEW_H

#include <gtkmm.h>
#include <gdkmm.h>
#include <list>
#include "DeckGUI.h"
#include "../Model/GameLogic.h"
#include "../Controller/Controller.h"
#include "Observer.h"
#include "../Card.h"
#include "PlayerBox.h"
#include "MenuBox.h"

class MenuBox;

class View : public Gtk::Window, public Observer {
public:
        View(Controller * controller, GameLogic * gameLogic); // where gameLogic is the common interface using facade pattern
        virtual ~View();
        virtual void update();
        void restart();
        PlayerBox * getPlayerBox(int index);

private:
        class PopupMessage : public Gtk::Dialog { //popup window/dialog for invalid moves or round finishes messages
        public:
                PopupMessage(Gtk::Window &main, std::string title, std::string message);
                
        private:
                Gtk::Label msg;
        };

        GameLogic * gameLogic_; //game logic is the model
        Controller * controller_; //controller

        Gtk::Table table; //top level container

        DeckGUI deck_;

        MenuBox * menuBox_; //inherits from HBox

        Gtk::Frame cardFrame_; //table
        Gtk::Table cardTableView_;
        Gtk::Image *clubs_[13];
        Gtk::Image *diamonds_[13];
        Gtk::Image *hearts_[13];
        Gtk::Image *spades_[13];

        PlayerBox playerBox_[4]; //player stats and view
        Gtk::HBox playerHBox_; //container for player boxes

        Gtk::HBox handBox_; //container for current hand
        Gtk::Frame handBoxFrame_;
        Gtk::Button handButton_[13];
        Gtk::Image *hand_[13];

        const double progressMax_ = 52;
        double progress_ = 0;

        void onCardClicked(int index);
        void onRageButtonClicked();
};

#endif