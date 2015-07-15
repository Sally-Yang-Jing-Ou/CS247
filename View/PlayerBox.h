#ifndef PLAYERBOX_H
#define PLAYERBOX_H

#include <gtkmm.h>

class PlayerBox : public Gtk::Frame { //this is where the player's stats are displayed in
        public:
                PlayerBox();    
                void activate(bool active);
                void setScore(std::string score);
                void setDiscards(std::string discards);
                Gtk::Button& rageButton();

        private:
                Gtk::Label score_;
                Gtk::Label discard_;
                Gtk::VBox playerVBox_;
                Gtk::Button rageButton_;
                
        };

#endif