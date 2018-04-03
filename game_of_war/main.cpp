#include <iostream>
#include <cassert>
// #include "card.hpp"
#include "bitCard.hpp"
// #include "union_card.hpp"
int main()
{

	/*StandardCard c{Ace,Spades};
	JokerCard c2(Red);

	std::cout << c << std::endl;
	std::cout << c2 << std::endl;*/

	
	/*Bitcard tests*/
	Card c(Ace,Spades);
	assert(c.is_standard());
	std::cout << "assert is_standard working" << std::endl;

	Card c2(Red);
	assert(c2.is_joker());
	std::cout << "assert is_joker working"<< std::endl;

	Rank r = c.get_rank();
	Suit r2 = c.get_suit();
	std::cout << "assert get_suit / get_rank working"<< std::endl;

	Color col = c2.get_color();
	std::cout << "assert get_color working"<< std::endl;

	std::cout << c << std::endl;
	std::cout << c2 << std::endl;

	
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