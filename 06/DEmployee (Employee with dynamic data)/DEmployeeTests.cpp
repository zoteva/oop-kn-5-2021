#include "DEmployee.h"

#include <iostream>

int main()
{
	DEmployee me("Me", "Teacher", 1300);
	//me.print();

	//me.setName("You");
	//me.print();

	// copy constructor
	DEmployee copy = me;
	//copy.print();

	copy.setName("Copy");

	std::cout << "Show me after changing the copy: " << std::endl;
	me.print();

	std::cout << "Show copy after the change: " << std::endl;
	copy.print();

	// assignment operator
	me = copy;
	me.print();

	me.setName("Changed");

	me.print();
	copy.print();

	return 0;
}