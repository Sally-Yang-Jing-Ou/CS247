#ifndef LOGGER_H
#define LOGGER_H

#include <gtkmm.h>
#include "../Model/GameLogic.h"
#include "../Controller/Controller.h"

class Logger : public Gtk::Frame, public Observer {
        public:
                Logger(Controller * controller, GameLogic * gameLogic);
                ~Logger();
                virtual void update();
        private:
                GameLogic * gameLogic_; 
                Controller * controller_;

                Gtk::TextView logView_;
                Gtk::ScrolledWindow scroller_;
        };

#endif