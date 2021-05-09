#include "Static.h"

#include <iostream>

// extern const int g_c;
const int g_c { 3 };

// forward declarations
extern int g_var;
extern const int g_ec;
//extern int g_svar;

int g_svar;


void showGlobal();

int main()
{
	std::cout << "Global constant: " << &g_c << std::endl;
	std::cout << "Forwarded non-constant global: " << &g_var << std::endl;
	std::cout << "Forwarded Global external constant: " << &g_ec << std::endl;
	std::cout << "Forwarded Global static variable: " << &g_svar << std::endl;

	showGlobal();

	return 0;
}