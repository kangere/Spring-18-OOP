#ifndef BITCARD_HPP
#define BITCARD_HPP

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
	unsigned char bits;

public:
	Card() {}

	Card(Rank r, Suit s):
	 	bits((unsigned)s << 4 | (unsigned)r) {}

	Rank get_rank  () const { 
		return (Rank) (0b001111 & bits);
	}

	Suit get_suit () const { 
		return (Suit) ((0b110000 & bits) >> 4); 
	}

	bool operator==(const Card &c)
	{ return bits == c.bits; }

	bool operator!=(const Card &c)
	{ return bits != c.bits; }

	bool operator>(const Card &c)
	{ return bits > c.bits; }

	bool operator<(const Card &c)
	{ return bits < c.bits; }

	bool operator<=(const Card &c)
	{ return bits <= c.bits; }

	bool operator>=(const Card &c)
	{ return bits >= c.bits; }


};






#endif