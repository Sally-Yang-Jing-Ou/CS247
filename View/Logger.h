#ifndef LOGGER_H
#define LOGGER_H

#include <gtkmm.h>
#include "../Model/GameLogic.h"
#include "../Model/Log.h"
#include "../Controller/Controller.h"

/*
The logger view
*/
class Logger : public Gtk::Frame, public Observer {
        public:
                Logger(Controller * controller, GameLogic * gameLogic, Log * log); //constructor
                ~Logger(); //destructor
                virtual void update(); //updates view
                void clearLog(); //clears the log
                void message(std::string msg); 

        private:
                GameLogic * gameLogic_; //reference to gameLogic
                Controller * controller_; //reference to the controller
                Log * log_; //reference to the log model

                Gtk::TextView logView_; //the actual view
                Gtk::ScrolledWindow scroller_; //the scroller
        };

#endif