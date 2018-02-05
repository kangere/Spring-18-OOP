#include <iostream>
#include "string.cpp"

int main ()
{
	std::cout << "Hello" << std::endl;

	// Default construct
	String s0;

	// Construct and assign from a literal value
	String s1 = "hello";
	s1 = "foo";

	// Copy construct and assign
	String s2 = s1;
	s2 = s1; 

	// Compare
	std::cout << (s1 == s1) << std::endl;

	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;

	// Order
	std::cout << (s1 < s1) << std::endl; // lexicographical compariso

	// Object independence
	s2 = "bar"; // Does not change the value of s1
	
	std::cout << s2 << " " << s1 << std::endl;
	return 0;
}