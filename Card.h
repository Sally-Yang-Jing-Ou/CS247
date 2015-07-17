#ifndef _CARD_
#define _CARD_

#include <ostream>
#include <istream>
#include <string>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card{
	friend std::istream &operator>>(std::istream &, Card &);

public:
	Card(Suit, Rank); //constructor
	Suit getSuit() const; //getter for suit
	Rank getRank() const; //getter for rank
	std::string getRankInString () const; //getter for rank casted to string

private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const Card &, const Card &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif
