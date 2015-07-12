#ifndef VIEW_H
#define VIEW_H

#include <gtkmm.h>
#include <list>
#include "DeckGUI.h"
#include "../Model/GameLogic.h"
#include "../Controller/Controller.h"
#include "Observer.h"
#include "../Card.h"

class View : public Gtk::Window, public Observer {
public:
        View(Controller * controller, GameLogic * gameLogic); // where gameLogic is the common interface using facade pattern
        virtual ~View();
        virtual void update();

protected:
        virtual void onStartButtonClicked();
        // virtual void onCardClicked(int index);
        // virtual void onRageClicked();
        // virtual void onEndButtonClicked();

private:
        static const int NUMBER_OF_CARDS = 13;
        static const int NUMBER_OF_PLAYERS = 4;

        DeckGUI deck_;

        //top row
        Gtk::VBox container_;
        Gtk::HBox menuBox_;
        Gtk::Entry seedField_;
        Gtk::Label seedLabel_;
        Gtk::Button startButton_;
        Gtk::Button endButton_;

        //card table
        Gtk::Frame cardFrame_;
        Gtk::Table cardTableView_;
        Gtk::Image *clubs[NUMBER_OF_CARDS];
        Gtk::Image *diamonds[NUMBER_OF_CARDS];
        Gtk::Image *hearts[NUMBER_OF_CARDS];
        Gtk::Image *spades[NUMBER_OF_CARDS];


        //player view


        //Hand
        Gtk::HBox handBox_;
        Gtk::Frame handBoxFrame_;
        Gtk::Button handButton[NUMBER_OF_CARDS];
        Gtk::Image *hand[NUMBER_OF_CARDS];

        //model and controller
        GameLogic * gameLogic_;
        Controller * controller_;
};

#endif
                
                // Gtk::Table outerTable;

                // //Top Row
                // Gtk::HBox menuHBox;
                // Gtk::Button startGameButton;
                // Gtk::Button endGameButton;
                // Gtk::Entry seedEntry;
                
                // //Card Table Display
                // Gtk::Frame cardFrame;
                // Gtk::Table cardTable;
                // Gtk::Image *clubs[NUMBER_OF_CARDS_IN_ROW];
                // Gtk::Image *diamonds[NUMBER_OF_CARDS_IN_ROW];
                // Gtk::Image *hearts[NUMBER_OF_CARDS_IN_ROW];
                // Gtk::Image *spades[NUMBER_OF_CARDS_IN_ROW];
                
                // //Player Views
                // PlayerFrame playerFrames[NUMBER_OF_PLAYERS];
                // Gtk::HBox playerHBox;           

                // void reset();
