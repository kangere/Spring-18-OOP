#include "rational.hpp"
#include <iostream>
#include <cassert>

int main()
{

	rational r(1,2);
	rational r1(-1,-2);
	rational r2(3,4);


	
	assert(r == r1);
	std::cout <<"== success" <<std::endl;
	assert(r != r2);
	std::cout <<"!= success" <<std::endl;
	assert(r < r2);
	std::cout <<"< success" <<std::endl;
	assert(r2 > r);
	std::cout <<"> success" <<std::endl;
	assert(r <= r2);
	std::cout <<"<= success" <<std::endl;
	assert(r2 >= r1);
	std::cout <<">= success" <<std::endl;
	

	return 0;
}