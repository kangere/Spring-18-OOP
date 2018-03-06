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


rational rational::operator+(const rational &r)
{
	int numerator;
	int num_lcm = lcm(denom,r.denom);

	numerator = ((num_lcm / denom) * num) + ((num_lcm / r.denom) * r.num);

	return rational(numerator,num_lcm); 
}

rational rational::operator-(const rational &r)
{
	int numerator;
	int num_lcm = lcm(denom,r.denom);

	numerator = ((num_lcm / denom) * num) - ((num_lcm / r.denom) * r.num);

	return rational(numerator,num_lcm); 
}

rational rational::operator*(const rational &r)
{
	return rational(num * r.num, denom * r.denom);
}

rational rational::operator/(const rational &r)
{
	return rational(num * r.denom, denom * r.num);
}

std::ostream &operator<<(std::ostream &out,rational r)
{
	out << r.numerator() << '/' << r.denominator();
	return out;	
}

// std::istream& operator>>(std::istream& in, rational& r)
// {
// 	int n,d;
	
// 	in >> n;
// 	in >> r.denom;

// 	r.num =  n;
// 	 r.denom = d;
// 	return in;	
// }