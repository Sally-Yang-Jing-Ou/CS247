#ifndef PLAYERBOX_H
#define PLAYERBOX_H

#include <gtkmm.h>

class PlayerBox : public Gtk::Frame { //this is where the player's stats are displayed in
        public:
                PlayerBox(); //constructor
                void activate(bool active); //activates playerBox
                void setScore(std::string score); //setter for the score
                void setDiscards(std::string discards); //setter for discards
                Gtk::Button& rageButton(); //widget for ragequit button

        private:
                Gtk::Label score_; //the label "Score: "
                Gtk::Label discard_; //the label for "Discards: "
                Gtk::VBox playerVBox_; //container for player boxes
                Gtk::Button rageButton_; //button widget for ragequit
                
        };

#endif