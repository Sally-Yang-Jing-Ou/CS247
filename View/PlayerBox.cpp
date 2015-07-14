#include "PlayerBox.h"

using namespace std;

PlayerBox::PlayerBox() : playerVBox_(true, 1), rageButton_("Ragequit!"), scoreLabel_("0 points", Gtk::ALIGN_CENTER),
						discardLabel_("0 discards", Gtk::ALIGN_CENTER) {

	set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);
	set_shadow_type(Gtk::SHADOW_ETCHED_OUT);	
	playerVBox_.add(rageButton_);
	playerVBox_.add(scoreLabel_);
	playerVBox_.add(discardLabel_);
	rageButton_.set_sensitive(false);
	add(playerVBox_);
}

void PlayerBox::activate(bool active) {
	rageButton_.set_sensitive(active);
}

void PlayerBox::scoreSetter(string score) {
	string label = score + " points";
	scoreLabel_.set_label(label);
}

void PlayerBox::discardsSetter(string discardCount) {
	string label = discardCount + " discards";
	discardLabel_.set_label(label);
}

Gtk::Button& PlayerBox::rageButton() {
	return rageButton_;
}

PlayerBox::~PlayerBox() {
	
}
