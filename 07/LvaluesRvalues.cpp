#include <iostream>

int getValue()
{
	return 5;
}

void increment(int& x)
{
	++x;
}

void print(const int& x)
{
	std::cout << x << std::endl;
}

void function(int& x)
{
	std::cout << "[lvalue] reference" << std::endl;
}

void function(int&& x)
{
	std::cout << "[rvalue] reference" << std::endl;
}

int main()
{
	int x = 5;
	x = getValue();

	int y = x + 5;

	increment(x);
	//increment(5);
	//increment(getValue());
	increment(y);
	//increment(x + 5);

	print(x);
	print(5);
	print(getValue());

	int& rx = x;
	//int& r5 = 5;

	int&& rr = x + 5;
	int&& rrf = getValue();
	//int&& rrx = x;

	function(rx);
	function(x);
	function(x + 5);
	function(getValue());

	return 0;
}