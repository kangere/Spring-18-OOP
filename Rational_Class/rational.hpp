#ifndef RATIONAL_HPP
#define RATIONAL_HPP



class rational {

private:
	int num, denom;
	void simplify();
	int gcd(int,int);
	int lcm (int, int);

public:
	//constructors
	rational():num(0), denom(1) {}
	rational(int num):num(num), denom(1)
		{}
	rational(int,int);

	bool operator==(const rational &);
	bool operator!=(const rational &);

	bool operator<(const rational &);
	bool operator>(const rational &);
	bool operator<=(const rational &);
	bool operator>=(const rational &);




};




#endif