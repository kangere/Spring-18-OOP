#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
class String 
{
private:
	char *buffer;
	int len;

public:
	int length() const {return len;}
	String():buffer(nullptr), len(0){}
	String(const String&);
	String(const char*);

	void operator=(const String &);
	void operator=(const char*);
	bool operator==(const String&);
	bool operator<(const String&);

	friend std::ostream& operator <<(std::ostream&, const String&);

	~String(){delete [] buffer;}
	
};



#endif