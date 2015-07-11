#ifndef VIEW_H
#define VIEW_H

#include <gtkmm.h>
#include "DeckGUI.h"
#include "GameLogic.h"

class View : public Gtk::Window {
public:
        View(GameLogic * gameLogic); // where gameLogic is the common interface using facade pattern
        virtual ~View();
private:
        Gtk::VBox container_;
        Gtk::HBox menuBox_;
        DeckGUI deck_;
        Gtk::HBox handBox_;
        Gtk::Frame handBoxFrame_;
        Gtk::Button startButton_;
        Gtk::Entry seedField_;
        Gtk::Label seedLabel_;

        virtual void onStartButtonClicked();
};

#endif
