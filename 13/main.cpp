#include "BinaryOperation.h"
#include "Conditional.h"
#include "Constant.h"
#include "Formula.h"
#include "Read.h"

int main()
{
	Constant two(2);
	Constant three(3);

	// (2 + 3) * 5
	BinaryOperation lhs('+', &two, &three);

	Constant five(5);
	Read r;
	BinaryOperation bo('*', &lhs, &r);

	bo.print();
	std::cout << "\nValue: " << bo.value() << std::endl;
 
	BinaryOperation condition('<', &r, &five);
	Conditional test(&condition, &two, &three);
	test.print();

	// извежда 2, ако поребителят въведе число, 
	// което е по-малко от 5 и 3 в противен случай
	std::cout << "\nValue: " << test.value() << std::endl; 
			
	Conditional copy = test;
	copy.print();

	return 0;
}