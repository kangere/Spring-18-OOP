#include <iostream>
#include <cassert>
// #include "card.hpp"
/*#include "bitCard.hpp"
*/
#include "union_card.hpp"
int main()
{

	StandardCard sc{Ace,Spades};
	Card c{sc};

	assert(c.is_standard());
	 
	return 0;
}