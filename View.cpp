#include "view.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

View::View(Controller * controller, GameLogic * gameLogic) : gameLogic_(gameLogic), controller_(controller), container_(true, 10), handBox_(true, 10), startButton_("Start game"), seedLabel_("Seed: ") {
    set_title("Straights");

    seedField_.set_text("0");
    menuBox_.pack_start(startButton_, false, false);
    menuBox_.pack_start(seedLabel_, false, false);
    menuBox_.pack_start(seedField_, false, false);
    startButton_.signal_clicked().connect( sigc::mem_fun( *this, &View::onStartButtonClicked ) );

    container_.pack_start(menuBox_);
    // vector< Glib::RefPtr<Gdk::Pixbuf> > handImages;
    // Gtk::Image * card[13];
    //
    // for (int i=0; i<13; ++i) {
    //     handImages.push_back(this->deck_.image((Rank)(i % 13), (Suit)(i % 4)));
    // }
    //
	// set_border_width( 10 );
    //
    // cout << Gtk::ALIGN_TOP << endl;
	// handBoxFrame_.set_label( "Hand:" );
	// handBoxFrame_.set_label_align( 0.5, Gtk::ALIGN_TOP +0.5);
	// handBoxFrame_.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
    //
	// add( handBoxFrame_ );
    //
	// handBoxFrame_.add( handBox_ );
    //
	// for (int i = 0; i < 13; i++ ) {
	// 	card[i] = new Gtk::Image( handImages.at(i) );
	// 	handBox_.add( *card[i] );
	// }
    //
    add(container_);
    show_all();
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
}

View::~View() {}
