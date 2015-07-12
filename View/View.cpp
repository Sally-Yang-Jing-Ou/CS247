#include "view.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

View::View(Controller * controller, GameLogic * gameLogic) : gameLogic_(gameLogic), controller_(controller), container_(true, 10), handBox_(true, 10), startButton_("Start game"), endButton_("End Current Game"), 
                                                            seedLabel_("Seed: "), cardTableView_(4, NUMBER_OF_CARDS, true), menuBox_(true,2), table(4) {
    set_title("Straights");

    seedField_.set_text("0");
    menuBox_.pack_start(startButton_, false, false);
    menuBox_.pack_start(seedLabel_, false, false);
    menuBox_.pack_start(seedField_, false, false);
    menuBox_.pack_start(endButton_, false, false);
    startButton_.signal_clicked().connect( sigc::mem_fun( *this, &View::onStartButtonClicked ) );
    endButton_.signal_clicked().connect(sigc::mem_fun(*this, &View::onEndButtonClicked));

    //container_.pack_start(menuBox_);

    table.attach(menuBox_, 0, 1, 0, 1);

    cardFrame_.set_label("Table");
    cardFrame_.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    cardFrame_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    cardTableView_.set_col_spacings(1);
    cardTableView_.set_row_spacings(2);

    //table view for cards
    for(int r = ACE; r < RANK_COUNT; r++) {
        clubs[r] = new Gtk::Image(deck_.null());
        cardTableView_.attach(*clubs[r], r, r+1, CLUB, CLUB+1);
        diamonds[r] = new Gtk::Image(deck_.null());
        cardTableView_.attach(*diamonds[r], r, r+1, DIAMOND, DIAMOND+1);
        hearts[r] = new Gtk::Image(deck_.null());
        cardTableView_.attach(*hearts[r], r, r+1, HEART, HEART+1);
        spades[r] = new Gtk::Image(deck_.null());
        cardTableView_.attach(*spades[r], r, r+1, SPADE, SPADE+1);
    }

    cardFrame_.add(cardTableView_);

	handBoxFrame_.set_label( "Hand:" );
	handBoxFrame_.set_label_align( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
	handBoxFrame_.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
    //container_.pack_start(handBoxFrame_);

    for (int i = 0; i < 4; i++) {
        playerBox_[i].rageButton().signal_clicked().connect(sigc::mem_fun(*this, &View::onRageButtonClicked));
        stringstream stream;
        stream << (i+1);
        string currentPlayer = "Player " + stream.str();
        playerBox_[i].set_label(currentPlayer);
        playerHBox_.add(playerBox_[i]);
    }

    //Setup the hand
    for (int i = 0; i < NUMBER_OF_CARDS; i++) {
        hand_[i] = new Gtk::Image(deck_.null());
        handButton_[i].set_image(*hand_[i]);
        handButton_[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &View::onCardClicked), i));
        handBox_.add(handButton_[i]);
    }

    handBoxFrame_.add( handBox_ );

    table.attach(playerHBox_, 0, 1, 2, 3);
    table.attach(cardFrame_, 0, 1, 1, 2);
    table.attach(handBoxFrame_, 0, 1, 3, 4);
    add(table);

    //add(container_);
    show_all();
    gameLogic_->subscribe(this);
}

void View::onStartButtonClicked() {
    //set seed
    string seed = seedField_.get_text();
    gameLogic_->setSeed(atoi(seed.c_str()));

    //invite players
    for (int i = 0; i < 4; i++) {
        Gtk::Dialog dialog( "Invite Players", *this );
        stringstream sstm;
        sstm << "Is player " << i << " a human or computer player?";
        string promptText = sstm.str();
        Gtk::Label prompt(promptText);

        Gtk::VBox* contentArea = dialog.get_vbox();
        contentArea->pack_start(prompt, true, false);
        prompt.show();

        dialog.add_button("Human", 0);
        dialog.add_button("Computer", 1);

    	int result = dialog.run();
        controller_->onPlayerOptionChosen(result);
    }

    //gameLogic_->addSubscriptions(this);
    gameLogic_->beginGame();
}

void View::update() {
    // cout << "clear" << endl;
    // GList *children, *iter;
    //
    // children = gtk_container_get_children(GTK_CONTAINER(&handBox_));
    // for(iter = children; iter != NULL; iter = g_list_next(iter)) {
    //     gtk_widget_destroy(GTK_WIDGET(iter->data));
    // }
    // g_list_free(children);

    list<Card*> currentHand = gameLogic_->getHandForCurrentPlayer();
    for (std::list<Card*>::iterator it = currentHand.begin(); it != currentHand.end(); it++) {
        Glib::RefPtr<Gdk::Pixbuf> buffer = this->deck_.image((*it)->getRank(), (*it)->getSuit());
        Gtk::Image * card = new Gtk::Image( buffer );
        handBox_.add( *card );
    }

    show_all();
}

void View::onEndButtonClicked() {

}

void View::onCardClicked(int index){

}

void View::onRageButtonClicked(){

}

View::~View() {}
