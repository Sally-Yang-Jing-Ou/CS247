#include <string>
#include "HandBox.h"

using namespace std;

HandBox::HandBox(Controller * controller, GameLogic * gameLogic, View * window, DeckGUI *deck): gameLogic_(gameLogic), controller_(controller), mainWindow_(window), handBox_(true, 10), deck_(deck) {

    set_label( "Hand:" );
    set_label_align( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    set_shadow_type( Gtk::SHADOW_ETCHED_OUT );

    Gdk::Color dflt("white smoke");
    for (int i = 0; i < 13; i++) {
        hand_[i] = new Gtk::Image(deck_->null());
        handButton_[i].modify_bg(Gtk::STATE_NORMAL, dflt);
        handButton_[i].modify_bg(Gtk::STATE_PRELIGHT, dflt);
        handButton_[i].set_image(*hand_[i]);
        handButton_[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &HandBox::onCardClicked), i));
        handBox_.add(handButton_[i]);
    }

    add(handBox_);
}

void HandBox::setHand(int index, Glib::RefPtr<Gdk::Pixbuf> buffer) {
    hand_[index]->set(deck_->null());
}

void HandBox::onCardClicked(int index){
    try{
        controller_->onCardClicked(index);
     } catch (GameLogic::InvalidMoveException ex) {
        PopupMessage dialog(*mainWindow_, "Invalid Move", ex.getMessage());
    }
}

void HandBox::update() {
    // initially blanks all buttons
    Gdk::Color dflt("white smoke");
    for (int handIndex = 0; handIndex<13; ++handIndex) {
        handButton_[handIndex].modify_bg(Gtk::STATE_NORMAL, dflt);
        handButton_[handIndex].modify_bg(Gtk::STATE_PRELIGHT, dflt);
    }   

    list<Card*> currentHand = gameLogic_->getHandForCurrentPlayer();
    bool legalPlayExists = false;
    Gdk::Color limeGreen("lime green");
    Gdk::Color lime("lime");
    
    int i = 0;
    for (std::list<Card*>::iterator it = currentHand.begin(); it != currentHand.end(); it++) {
        hand_[i]->set(deck_->image((*it)->getRank(), (*it)->getSuit()));

        if (gameLogic_->isCardLegal(**it)) {
            legalPlayExists = true;
            handButton_[i].modify_bg(Gtk::STATE_NORMAL, limeGreen);
            handButton_[i].modify_bg(Gtk::STATE_PRELIGHT, lime);
        } 

        i++;
    }

    Gdk::Color tomato("tomato");
    Gdk::Color red("red");
    if (!legalPlayExists) {
        for (int j=0; j<i; ++j) {
            handButton_[j].modify_bg(Gtk::STATE_NORMAL, red);
            handButton_[j].modify_bg(Gtk::STATE_PRELIGHT, tomato);
        }
    }

    // blanks the rest of the buttons
    while(i < 13) {
        hand_[i]->set(deck_->null());
        i++;
    }
}