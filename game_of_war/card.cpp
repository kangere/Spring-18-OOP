#include "card.hpp"
#include <iostream>

Deck::Deck(const Deck& deck)
{
	for(Card *c: deck)
	{
		Card new = c->clone();
		*this.push_back(&new);
	}

}

StandardCard StandardCard::clone()
{
	return new StandardCard(this->get_rank(),this->get_suit());
}

JokerCard JokerCard::clone()
{
	return new JokerCard(this->get_color());
}
std::ostream& operator<<(std::ostream& os, const StandardCard& card)
{
	os << rank_name[card.rank] << " " << suit_name[card.suit];

	return os;
}

std::ostream& operator<<(std::ostream &os, const JokerCard &card )
{
	os << color_name[card.color] ;

	return os;
}