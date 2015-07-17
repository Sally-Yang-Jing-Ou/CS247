#include <string>
#include "PlayerBox.h"

using namespace std;

//constructor for playerBox - where each player's stats are
PlayerBox::PlayerBox() : playerVBox_(true, 1), rageButton_("Ragequit!"), score_("0 points", Gtk::ALIGN_CENTER),
                        discard_("0 discards", Gtk::ALIGN_CENTER) {

    set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);
    playerVBox_.add(rageButton_);
    playerVBox_.add(score_);
    playerVBox_.add(discard_);
    rageButton_.set_sensitive(false);
    add(playerVBox_);
}

void PlayerBox::activate(bool active) {
    rageButton_.set_sensitive(active);
}

void PlayerBox::setScore(string score) {
    string label = score + " points";
    score_.set_label(label);
}

void PlayerBox::setDiscards(string discardCount) {
    string label = discardCount + " discards";
    discard_.set_label(label);
}

Gtk::Button& PlayerBox::rageButton() {
    return rageButton_;
}