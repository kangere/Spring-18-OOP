#include <iostream>
// #include "card.hpp"
#include "bitCard.hpp"


int main()
{

	 Card c{Ace,Hearts};
	 
	std::cout << "Card Size: "<< sizeof(c) << std::endl;
	std::cout << "int Size: "<< sizeof(int) << std::endl;

	return 0;
}