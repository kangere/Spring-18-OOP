#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iosfwd>

class rational {

private:
	int num, denom;
	void simplify();
	int gcd(int,int);
	int lcm (int, int);

public:
	//constructors
	rational():num(0), denom(1) {}
	rational(int number):num(number), denom(1) {}
	rational(int,int);

	int numerator() const {return num;}
	int denominator() const {return denom;}

	
	bool operator==(const rational &);
	bool operator!=(const rational &);

	bool operator<(const rational &);
	bool operator>(const rational &);
	bool operator<=(const rational &);
	bool operator>=(const rational &);

	rational operator+(const rational &);
	rational operator*(const rational &);
	rational operator-(const rational &);
	rational operator/(const rational &);

	friend std::ostream& operator<<(std::ostream &, const rational &);
	friend std::istream& operator>>(std::istream &, rational &);




};






#endif