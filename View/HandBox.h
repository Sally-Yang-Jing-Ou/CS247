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
                HandBox(Controller * controller, GameLogic * gameLogic, View * window, DeckGUI * deck);
                virtual ~HandBox();
                void setHand(int index, Glib::RefPtr<Gdk::Pixbuf> buffer);
                virtual void update();
        private:
                GameLogic * gameLogic_; //game logic is the model
                Controller * controller_; //controller

                View * mainWindow_; //handle to main window

                Gtk::HBox handBox_; //container for current hand
                Gtk::Button handButton_[13];
                Gtk::Image *hand_[13];

                DeckGUI * deck_;

                void onCardClicked(int index);
        };

#endif