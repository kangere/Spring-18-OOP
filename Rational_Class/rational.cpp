#include "rational.hpp"
#include <cstdlib>
#include <cassert>

int rational::gcd(int a, int b)
{
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

int rational::lcm(int a, int b)
{
  return (std::abs(a) / gcd(a, b)) * std::abs(b);
}

void rational::simplify()
{
	auto gcdVal = gcd(num,denom);

	num /= gcdVal;
	denom /= gcdVal;

	if(denom < 0 && num < 0)
	{
		denom = std::abs(denom);
		num = std::abs(num);
	}
	else if(denom < 0)
	{
		denom = std::abs(denom);
		num *= -1;
	}

}

rational::rational(int num,int den)
{
	this->num = num;
	assert(den != 0);
	denom = den;
	simplify();
}



bool rational::operator==(const rational &r)
{
	return (num * r.denom) == (r.num * denom);
}

bool rational::operator!=(const rational &r)
{
	return !(*this == r);
}

bool rational::operator<(const rational &r)
{
	return ((num * r.denom) < (r.num * denom));
}

bool rational::operator>(const rational &r)
{
	return !(*this < r);
}

bool rational::operator<=(const rational &r)
{
	return (*this < r) || (*this == r);
}

bool rational::operator>=(const rational &r)
{
	return(*this > r) || (*this == r);
}