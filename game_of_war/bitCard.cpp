#include "bitCard.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream &os, const Card &card)
{
	if(card.is_joker())
	{
		os << color_name[card.get_color()];
	}
	else if(card.is_standard())
	{
		os << rank_name[card.get_rank()] << " " << suit_name[card.get_suit()];
	}

	return os;
}