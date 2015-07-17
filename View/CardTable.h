#ifndef CARDTABLE_H
#define CARDTABLE_H

#include <gtkmm.h>
#include "../Model/GameLogic.h"
#include "../Controller/Controller.h"
#include "DeckGUI.h"

class CardTable : public Gtk::Frame {
        public:
                CardTable(Controller * controller, GameLogic * gameLogic, DeckGUI * deck); //constructor
                ~CardTable(); //destructor
                virtual void update(); //updates the view
                void prepareForRestart(); //cleans up view to prepare for game restart
        private:
                GameLogic * gameLogic_; //reference to gameLogic
                Controller * controller_; //reference to controller

                DeckGUI * deck_; //reference to deck

                Gtk::Table cardTableView_;
                Gtk::Image *clubs_[13]; //holds club card images
                Gtk::Image *diamonds_[13]; //holds diamond card images
                Gtk::Image *hearts_[13]; //holds heart card images
                Gtk::Image *spades_[13]; //holds spades card images
        };

#endif