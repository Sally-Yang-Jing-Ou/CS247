#include "PopupMessage.h"

using namespace std;
//taken from example 06
PopupMessage::PopupMessage(Gtk::Window &main, string title, string message): Dialog( title, main, true, true ), msg(message, Gtk::ALIGN_LEFT) {
	Gtk::VBox* contentArea = this->get_vbox();
	contentArea->add(msg);

	Gtk::Button * closeButton = add_button( Gtk::Stock::CLOSE, Gtk::RESPONSE_CLOSE);
	show_all_children();

	run ();
}
