#ifndef CARDTABLE_H
#define CARDTABLE_H

#include <gtkmm.h>
#include "../Model/GameLogic.h"
#include "../Controller/Controller.h"
#include "DeckGUI.h"
#include "CardTable.h"

class CardTable : public Gtk::Frame {
        public:
                CardTable(Controller * controller, GameLogic * gameLogic, DeckGUI * deck);
                virtual void update();
                void prepareForRestart();
        private:
                GameLogic * gameLogic_; 
                Controller * controller_; 

                DeckGUI * deck_;

                Gtk::Table cardTableView_;
                Gtk::Image *clubs_[13];
                Gtk::Image *diamonds_[13];
                Gtk::Image *hearts_[13];
                Gtk::Image *spades_[13];
        };

#endif