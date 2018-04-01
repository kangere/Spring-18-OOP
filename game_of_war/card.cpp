#include "card.hpp"
#include <iostream>


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