#ifndef HANDBOX_H
#define HANDBOX_H

#include <gtkmm.h>
#include <gdkmm/pixbuf.h>
#include "../Model/GameLogic.h"
#include "../Controller/Controller.h"
#include <gdkmm.h>
#include "DeckGUI.h"
#include "PopupMessage.h"

class View;

class HandBox : public Gtk::Frame {
        public:
                HandBox(Controller * controller, GameLogic * gameLogic, View * window, DeckGUI * deck); //constructor
                virtual ~HandBox(); //destructor
                void setHand(int index, Glib::RefPtr<Gdk::Pixbuf> buffer); //sets card image for a specific card in the hand
                virtual void update(); //updates view
        private:
                GameLogic * gameLogic_; //game logic is the model
                Controller * controller_; //controller

                View * mainWindow_; //handle to main window

                Gtk::HBox handBox_; //container for current hand
                Gtk::Button handButton_[13]; //buttons for each card in the hand
                Gtk::Image *hand_[13]; //images for each button

                DeckGUI * deck_; // provides card images

                void onCardClicked(int index); //handler for card clicked
        };

#endif