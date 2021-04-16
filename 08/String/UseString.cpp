#include "String.h"

#include <iostream>

int main()
{ 
	String s;

	s = "abc";

	std::cout << std::boolalpha << (s == ("abd")) << std::endl;
	std::cout << s[1] << std::endl;

	s[1] = 'D';

	s += "new";
	std::cout << "Source: " << s << std::endl;
	
	String subStr = s(3, 8);
	std::cout << "Substring: " << subStr << std::endl;
	
	return 0;
}