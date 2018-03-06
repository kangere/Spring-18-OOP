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

	assert(r + r1 == rational(1,1));
	std::cout <<"+ success" <<std::endl;	

	assert(r2 - r == rational(1,4));
	std::cout <<"- success" <<std::endl;

	assert(r2 * r == rational(3,8));
	std::cout <<"* success" <<std::endl;

	assert(r2 / r == rational(3,2));
	std::cout <<"/ success" <<std::endl;	
	

	std::cout << r ;


	// rational r3;
	// std::cout << "Enter numerator and denominator: ";
	// std::cin >> r3;

	// std::cout << "Number is: " << r3 << std::endl;

	return 0;
}