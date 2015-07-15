#ifndef POPUPMESSAGE_H
#define POPUPMESSAGE_H

#include <gtkmm.h>
#include <string>
#include "view.h"

class View;

class PopupMessage : public Gtk::Dialog { //popup window/dialog for invalid moves or round finishes messages
public:
    PopupMessage(Gtk::Window &main, std::string title, std::string message);
        
private:
    Gtk::Label msg;
};

#endif