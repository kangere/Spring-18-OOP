#ifndef BITCARD_HPP
#define BITCARD_HPP

#define stringify(name) #name

#include <cassert>
#include <iosfwd>

const static char *rank_name[] =
{
	stringify(Ace),
	stringify(Two),
	stringify(Three),
	stringify(Four),
	stringify(Five),
	stringify(Six),
	stringify(Seven),
	stringify(Eight),
	stringify(Nine),
	stringify(Ten),
	stringify(Jack),
	stringify(Queen),
	stringify(King)
}; 

const static char *suit_name[] = 
{
	stringify(Hearts),
	stringify(Diamonds),
	stringify(Clubs),
	stringify(Spades)
};

const static char *color_name[] = 
{
	stringify(Black),
	stringify(Red)
};

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

enum Type {
	Joker,
	Standard
};

enum Color {
	Black,
	Red
};

class Card
{
private:
	unsigned char bits;
	

public:

	/*use 1 to indicate standard card*/
	Card(Rank r, Suit s):
	 	bits(1 << 6 | (unsigned)s << 4 | (unsigned)r) {}

	/*use 0 to indicate joker card*/
	Card(Color c):
	 	bits(0 << 6 | (unsigned)c) {}

	bool is_joker() const
	{return !((bits >> 6) & 1);}

	bool is_standard() const
	{return (bits >> 6) & 1;}

	Rank get_rank  () const { 
		assert(is_standard());
		return (Rank) (0b001111 & bits);
	}

	Suit get_suit () const { 
		assert(is_standard());
		return (Suit) ((0b110000 & bits) >> 4); 
	}

	Color get_color() const {
		assert(is_joker());
		return (Color)((0b000011 & bits));
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


	friend std::ostream& operator<<(std::ostream&, const Card&);
};






#endif