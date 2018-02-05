#ifndef CARD_HPP
#define CARD_HPP

enum Rank {
	Ace,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
};

enum Suit {
	Hearts,
	Diamonds,
	Clubs,
	Spades,
};

class Card
{
private:
	Rank rank;
	Suit suit;

public:
	Card(Rank r, Suit s):rank(r), suit(s){}
};

#endif
