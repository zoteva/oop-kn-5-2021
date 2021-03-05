#include <iostream>
#include <cstdio>

// try to rearange the members of the structure
// to minize the necessary memory

// a declaration of a structure
// no memory is allocated at this point
struct Sample
{
	double d;
	int i;
	char c;
};

// structure variables can be passed to functions (in this case by value)
void printStructureInfo(Sample s)
{
	std::cout << "Size of sample structure: " << sizeof(Sample) << std::endl;

	std::cout << "Structure variable s starts at " << &s << std::endl;
	std::cout << "s.d starts at " << &s.d << std::endl;
	std::cout << "s.i starts at " << &s.i << std::endl;
	std::cout << "s.c starts at " << reinterpret_cast<int*>(&(s.c)) << std::endl;
}

void print(const Sample& s)
{
	std::cout << "Values ( d = " << s.d << ", i =  " << s.i << ", c = " << s.c << " )" << std::endl;
}

int main()
{
	// uninitialized variable of type Sample 
	// the members are initialized with arbitrary values
	Sample s;
	print(s);

	// the members of the structure can be initialized using . (member selection operator)
	s.c = 'a';
	s.d = 5.0;
	s.i = 2;

	printStructureInfo(s);
	print(s);
	
	// the members of the structure are initialized with 0
	Sample s1{};
	print(s1);

	// using initializer list
	// the values have to be in the same order as in the declaration
	Sample s2{ 5.0, 2, 'b' };
	print(s2);

	return 0;
}