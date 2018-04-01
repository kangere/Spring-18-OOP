#ifndef	UNION_CARD_HPP
#define UNION_CARD_HPP

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

enum Color 
{
	Black,
	Red
};

enum Kind
{
	standard_card,
	joker_card
};

class StandardCard
{

private:
	Rank rank;
	Suit suit;

public:
	StandardCard(Rank rank, Suit suit)
	: rank(rank), suit(suit) {}
	
	Rank get_rank() const {return rank;}
	Suit get_suit() const { return suit;}	

};

class JokerCard
{
private:
	Color color;

public:
	JokerCard(Color color): color(color)
	{}

	Color get_color() const {return color;}

};

class Card
{

private:
	union Value
	{
		StandardCard sc;
		JokerCard jc;

		Value(StandardCard sc): sc(sc) {}
		Value(JokerCard jc): jc(jc) {}
	};

	Kind kind;
	Value val;

public:
	Card(StandardCard c): kind(standard_card), val(c)
	{}

	Card(JokerCard c): kind(joker_card), val(c)
	{}

	Rank get_rank () const;
	Suit get_suit () const;

	Color get_color () const;

	bool is_standard()
	{return kind == standard_card ? true : false;}

	bool is_joker()
	{return kind == joker_card ? true : false;}
};



#endif
