#ifndef CARD_HPP
#define CARD_HPP

#define stringify(name) #name

#include <iosfwd>

/*Card with inheritance*/
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



enum Color {
	Black,
	Red
};



class Card
{
private:
	

public:
	Card() {}
};

class StandardCard : public Card {
private:
	Rank rank;
	Suit suit;

public:
	StandardCard(Rank r, Suit s):
	rank(r), suit(s) {}

	Rank get_rank() const {return rank;}

	friend std::ostream& operator<<(std::ostream&, const StandardCard&); 

};

class JokerCard: public Card {
private:
	Color color;

public:
	JokerCard(Color c): 
	color(c) {}

	friend std::ostream& operator<<(std::ostream&,const JokerCard&);

};


#endif
