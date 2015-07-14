#ifndef _PLAYERBOX_
#define _PLAYERBOX_

#include <gtkmm.h>
#include <string>

class PlayerBox : public Gtk::Frame {
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

#endif