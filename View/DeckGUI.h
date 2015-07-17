#ifndef __DECK_GUI_H
#define __DECK_GUI_H
#include <gdkmm/pixbuf.h>
#include <vector>
#include "../Card.h"

class DeckGUI {
public:
	DeckGUI(); //constructor
	virtual ~DeckGUI(); //destructor
	Glib::RefPtr<Gdk::Pixbuf> image( Rank f, Suit s ); // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> null(); // Returns the image to use for the placeholder.
	const char* imageName(Rank f, Suit s); 

private:
	std::vector< Glib::RefPtr< Gdk::Pixbuf > > deck; // Contains the pixel buffer images.
};
#endif
