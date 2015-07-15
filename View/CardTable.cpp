#include <string>
#include "CardTable.h"
#include "../Card.h"

using namespace std;

CardTable::CardTable(Controller * controller, GameLogic * gameLogic, DeckGUI * deck): gameLogic_(gameLogic), controller_(controller), deck_(deck), cardTableView_(4, 13, true) {

    set_label("Table");
    set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    cardTableView_.set_col_spacings(1);
    cardTableView_.set_row_spacings(2);

    for(int i = ACE; i < 13; i++) {
        clubs_[i] = new Gtk::Image(deck_->null());
        cardTableView_.attach(*clubs_[i], i, i+1, 0, 1);
        diamonds_[i] = new Gtk::Image(deck_->null());
        cardTableView_.attach(*diamonds_[i], i, i+1, 1, 2);
        hearts_[i] = new Gtk::Image(deck_->null());
        cardTableView_.attach(*hearts_[i], i, i+1, 2, 3);
        spades_[i] = new Gtk::Image(deck_->null());
        cardTableView_.attach(*spades_[i], i, i+1, 3, 4);
    }

    add(cardTableView_);
}

void CardTable::update() {
    Card *mostRecentCard = gameLogic_->mostRecentCard();

    if (mostRecentCard->getSuit() == CLUB){
        clubs_[mostRecentCard->getRank()]->set(deck_->image(mostRecentCard->getRank(), mostRecentCard->getSuit()));
    } else if (mostRecentCard->getSuit() == DIAMOND){
        diamonds_[mostRecentCard->getRank()]->set(deck_->image(mostRecentCard->getRank(), mostRecentCard->getSuit()));
    } else if (mostRecentCard->getSuit() == SPADE){
        spades_[mostRecentCard->getRank()]->set(deck_->image(mostRecentCard->getRank(), mostRecentCard->getSuit()));
    } else if (mostRecentCard->getSuit() == HEART){
        hearts_[mostRecentCard->getRank()]->set(deck_->image(mostRecentCard->getRank(), mostRecentCard->getSuit()));
    }
}

void CardTable::prepareForRestart() {
    for (int i=0; i<13; ++i) {
        clubs_[i]->set(deck_->null());
        diamonds_[i]->set(deck_->null());
        hearts_[i]->set(deck_->null());
        spades_[i]->set(deck_->null());
    }
}