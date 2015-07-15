#include <gtkmm.h>

class PlayerBox : public Gtk::Frame { //this is where the player's stats are displayed in
        public:
                PlayerBox();    
                void activate(bool active);
                void scoreSetter(std::string score);
                void discardsSetter(std::string discards);
                Gtk::Button& rageButton();

        private:
                Gtk::Label score_;
                Gtk::Label discard_;
                Gtk::VBox playerVBox_;
                Gtk::Button rageButton_;
                
        };