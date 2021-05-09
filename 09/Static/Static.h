#pragma once

#include <iostream>

// functions have external linkage by default

// the definition of the function in the header file
// without inline will cause the linker to complain 
// for a multiple definitions of this function

inline void inlineFunction()
{
	std::cout << "Inline function" << std::endl;
}
