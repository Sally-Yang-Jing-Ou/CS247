#ifndef MENUBOX_H
#define MENUBOX_H

#include <gtkmm.h>
#include "../Model/GameLogic.h"
#include "../Controller/Controller.h"
#include <gdkmm.h>
#include "View.h"

class View;

class MenuBox : public Gtk::HBox {
        public:
            MenuBox(Controller * controller, GameLogic * gameLogic, View * window); //constructor
            virtual ~MenuBox(); //destructor
            void updateProgressBar(double increment); //updates progress bar
            void setController(Controller * controller); //setter for controller
        private:
            GameLogic * gameLogic_; //game logic is the model
            Controller * controller_; //controller

            View * mainWindow_; //handle to main window

            Gtk::Entry seedField_; //entry widget for "Seed: "
            Gtk::Label seedLabel_; //label for "Seed: "
            Gtk::Button startButton_; //button widget for starting the game
            Gtk::Button endButton_; //button widget for ending the game

            Gtk::Label progressLabel_; //label for progress
            Gtk::ProgressBar progressBar_; //progress bar that displays game progress

            void onStartButtonClicked(); //handler for start button clicked
            void onEndButtonClicked(); //handler for end button clicked
        };

#endif