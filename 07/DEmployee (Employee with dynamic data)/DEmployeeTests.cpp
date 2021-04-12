#include "DEmployee.h"

#include <iostream>

DEmployee functionToReturnLocalObjectByValue()
{
	DEmployee me("Me", "Teacher", 1300);
	return me;
}

void functionTakesArgumentByValue(DEmployee&& e)
{
	e.print();
}

int main()
{
	// functionTakesArgumentByValue(DEmployee{ "Me", "Teacher", 1300 });
	
	// functionToReturnLocalObjectByValue();

	DEmployee you{ "You", "Software developer", 2000 };
	you = DEmployee{ "Me", "Teacher", 1300 };

	return 0;
}