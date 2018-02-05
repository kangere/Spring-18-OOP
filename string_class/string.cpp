#include "string.hpp"
#include <string.h>

String::String(const String& other)
{
	len = other.length();

	buffer = new char[len];

	for(int i = 0; i < len; i++)
		buffer[i] = other.buffer[i];
}

String::String(const char* c)
{
	len = strlen(c);

	buffer = new char[len];

	for(int i = 0; i < len; i++)
		buffer[i] = *(c + i);
}


void String::operator=(const String &s)
{
	len = s.length();

	buffer = new char[len];

	for(int i = 0; i < len; i++)
		buffer[i] = s.buffer[i];
}

void String::operator=(const char* c)
{

	len = strlen(c);

	buffer = new char[len];

	for(int i = 0; i < len; i++)
		buffer[i] = *(c + i);
}

bool String::operator==(const String& s)
{
	if(len < s.length() || len > s.length())
		return false;

	for (int i = 0; i < len; i++)
	{
		if(buffer[i] != s.buffer[i])
			return false;
	}

	return true;
}
 bool String::operator<(const String& s)
 {
 	int  leftCount = 0, rightCount = 0;

 	for(int i = 0; i < len; i++)
 		leftCount += buffer[i];

 	for(int i = 0; i < s.length(); i++)
 		rightCount += s.buffer[i];

 	if(leftCount >= rightCount)
 		return false;

 	return true;

 	
 }

std::ostream &operator<<(std::ostream& stream, const String& string)
{
	for(int i =0; i < string.length(); i++)
		stream << string.buffer[i];

	return stream;
}
