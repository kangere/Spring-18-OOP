#include <iostream>
#include <cassert>
// #include "card.hpp"
#include "bitCard.hpp"

// #include "union_card.hpp"
int main()
{
	Card c(Ace,Spades);
	assert(c.is_standard());

	Card c2(Red);
	assert(c2.is_joker());
	/* union card tests
	StandardCard sc{Ace,Spades};
	Card c{sc};
	Card jc{JokerCard(Red)};

	assert(c.is_standard());
	std::cout << "Asser card is_standard working" << std::endl;
	assert(jc.is_joker());
	std::cout << "Asser card is_joker working" << std::endl;*/
	 
	return 0;
}