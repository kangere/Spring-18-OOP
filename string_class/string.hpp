#ifndef STRING_HPP
#define STRING_HPP

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

	
};



#endif