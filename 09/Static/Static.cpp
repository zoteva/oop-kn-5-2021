//#include "Static.h"

#include <iostream>

// const globals -- internal linkage by default
const int g_c{ 2 };

extern const int g_ec{ 12 };

// non-constant globals -- external linkage by default 
// unless static is used (a forward declaration cannot be used then)
int g_var{ 7 };

static int g_svar{ 71 };

// external linkage 
void showGlobal()
{
	std::cout << "-- Static.cpp--" << std::endl;
	std::cout << "Global internal constant: " << &g_c << std::endl;
	std::cout << "Global variable: " << &g_var << std::endl;
	std::cout << "Global external constant: " << &g_ec << std::endl;
	std::cout << "Global static variable: " << &g_svar << std::endl;
}