#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <utility>

// TODO: Write your JSON class hierarchy here
class Value 
{
public:
	Value(){}

	virtual void print() = 0;
};


class Bool:public Value
{
private:
	bool value;
public:
	Bool(bool value):value(value)
	{}

	void print();
};

class String: public Value 
{
private:
	std::string value;

public:
	String()
	{}

	String(std::string value): value(value)
	{}

	void print();
};

class Null: public Value  
{
public:
	Null(){}
	void print();
};

class Number: public Value
{
private:
	double number;

public:
	Number(double d): number(d)
	{}

	void print();
};

class Array: public Value
{
private:
	std::vector<Value*> array;

public:
	Array()
	{}
	void add(Value *v)
	{
		array.push_back(v);
	}
	
	void print();
};

class Object: public Value
{
private:
	std::map<String*,Value*> object;

public:
	Object()
	{}

	void add(String *key, Value *value)
	{
		std::pair<String*,Value*> item(key,value);
		object.insert(item);
	}

	void print();
};

Value* parse(const std::string&);