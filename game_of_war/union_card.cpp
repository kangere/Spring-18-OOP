#include "union_card.hpp"
#include <cassert>

Rank Card::get_rank() const
{
	assert(kind == standard_card);
	return val.sc.get_rank();
}

Suit Card::get_suit() const
{
	assert(kind == standard_card);
	return val.sc.get_suit();
}

Color Card::get_color() const
{
	assert(kind == joker_card);
	return val.jc.get_color();
}