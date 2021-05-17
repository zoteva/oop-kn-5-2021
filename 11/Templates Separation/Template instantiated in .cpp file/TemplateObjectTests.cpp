#include "TemplateObject.h"

#include <iostream>

int main()
{
	TemplateObject<int> intObject(2);
	std::cout << intObject.data << std::endl;

	return 0;
}