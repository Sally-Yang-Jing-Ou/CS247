#ifndef VIEW_H
#define VIEW_H

#include <gtkmm.h>
#include <list>
#include "DeckGUI.h"
#include "../Model/GameLogic.h"
#include "../Controller/Controller.h"
#include "Observer.h"
#include "PlayerBox.h"
#include "../Card.h"

class View : public Gtk::Window, public Observer {
public:
        View(Controller * controller, GameLogic * gameLogic); // where gameLogic is the common interface using facade pattern
        virtual ~View();
        virtual void update();

protected:
        virtual void onStartButtonClicked();
        virtual void onCardClicked(int index);
        virtual void onEndButtonClicked();
        virtual void onRageButtonClicked();

private:
        static const int NUMBER_OF_CARDS = 13;

        Gtk::Table table;

        DeckGUI deck_;

        Gtk::VBox container_; //menu
        Gtk::HBox menuBox_;
        Gtk::Entry seedField_;
        Gtk::Label seedLabel_;
        Gtk::Button startButton_;
        Gtk::Button endButton_;

        Gtk::Frame cardFrame_; //table
        Gtk::Table cardTableView_;
        Gtk::Image *clubs_[NUMBER_OF_CARDS];
        Gtk::Image *diamonds_[NUMBER_OF_CARDS];
        Gtk::Image *hearts_[NUMBER_OF_CARDS];
        Gtk::Image *spades_[NUMBER_OF_CARDS];

        PlayerBox playerBox_[4]; //player stats and view
        Gtk::HBox playerHBox_;

        Gtk::HBox handBox_; //current hand
        Gtk::Frame handBoxFrame_;
        Gtk::Button handButton_[NUMBER_OF_CARDS];
        Gtk::Image *hand_[NUMBER_OF_CARDS];

        //model and controller
        GameLogic * gameLogic_;
        Controller * controller_;

        void restart();
};

#endif