#ifndef VIEW_H
#define VIEW_H

#include <gtkmm.h>
#include <list>
#include "DeckGUI.h"
#include "GameLogic.h"
#include "Controller.h"
#include "Observer.h"
#include "Card.h"

class View : public Gtk::Window, public Observer {
public:
        View(Controller * controller, GameLogic * gameLogic); // where gameLogic is the common interface using facade pattern
        virtual ~View();
        virtual void update();
private:
        Gtk::VBox container_;
        Gtk::HBox menuBox_;
        DeckGUI deck_;
        Gtk::HBox handBox_;
        Gtk::Frame handBoxFrame_;
        Gtk::Button startButton_;
        Gtk::Entry seedField_;
        Gtk::Label seedLabel_;

        void onStartButtonClicked();

        GameLogic * gameLogic_;
        Controller * controller_;
};

#endif
