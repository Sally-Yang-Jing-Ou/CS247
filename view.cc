#include "view.h"
#include <vector>
#include <iostream>

using namespace std;

View::View() : handBox_(true, 10) {
    vector< Glib::RefPtr<Gdk::Pixbuf> > handImages;
    Gtk::Image * card[13];

    for (int i=0; i<13; ++i) {
        handImages.push_back(this->deck_.image((Rank)(i % 13), (Suit)(i % 4)));
    }

	set_border_width( 10 );

    cout << Gtk::ALIGN_TOP << endl;
	handBoxFrame_.set_label( "Hand:" );
	handBoxFrame_.set_label_align( 0.5, Gtk::ALIGN_TOP +0.5);
	handBoxFrame_.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );

	add( handBoxFrame_ );

	handBoxFrame_.add( handBox_ );

	for (int i = 0; i < 13; i++ ) {
		card[i] = new Gtk::Image( handImages.at(i) );
		handBox_.add( *card[i] );
	}

    show_all();
}

View::~View() {}
