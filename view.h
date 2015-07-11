#ifndef VIEW_H
#define VIEW_H

#include <gtkmm.h>
#include "DeckGUI.h"

class View : public Gtk::Window {
public:
        View();
        virtual ~View();
private:
        DeckGUI deck_;
        Gtk::HBox handBox_;
        Gtk::Frame handBoxFrame_;
};

#endif
