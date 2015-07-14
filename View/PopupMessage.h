#ifndef _POPUPMESSAGE_
#define _POPUPMESSAGE_

#include <gtkmm.h>
#include <string>

class PopupMessage : public Gtk::Dialog {
	public:
		PopupMessage(Gtk::Window &main, std::string title, std::string message);
		
	private:
		Gtk::Label msg;
};

#endif