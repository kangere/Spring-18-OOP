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

	return 0;
}