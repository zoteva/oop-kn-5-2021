#include <cassert>
#include <iostream>

// operations like +, -, *, /, comparisons (==, >, <, ...), =, access to an array element [], etc., 
// take constant time

// O(1)
double convertCelsiusToFahrenheit(double celsius)
{
    // all operations take constant time 
    // since they are primitive
    // the count of operations does not depend on the size of the input
    return (celsius * 9.0) / 5.0 + 32;
}

// check if a specified element is part of an array
bool isIn(const int* array, size_t size, int element)
{
    // constant time c1
    assert(array);

    // the assignment index = 0 takes constant time c2
    // inside the loop (the loop itself runs size times in worst case)
    // if statement:
    //     the comparison array[index] == element takes constant time
    //     the return statement takes constant time
    // overall if takes constant time c3
    // the increment ++index takes constant time c4
    // the comparison index < size takes constant time c5

    for (size_t index = 0; index < size; ++index)
    {
        if (array[index] == element)
            return true;
    }

    // contant time c6
    return false;

    // overall:
    // c1 + c2 + size*(c3 + c4 + c5) + c6
    // c + d*size
    // O(n)
    // when the size of the array is big enough, the constants will be insignificant
}

// what if the array is sorted?
bool isInSorted(const int* array, size_t n, int element)
{
    // constant time c1
    assert(array);

    // the assignment index = 0 takes constant time c2
    // inside the loop (the loop itself runs n times in worst case)
    // if statement:
    //     the comparison array[index] == element takes constant time
    //     the return statement takes constant time
    // overall if takes constant time c3
    // second if statement: constant time c4
    // the increment ++ index takes constant time c5
    // the comparison index < size takes constant time c6

    for (size_t index = 0; index < n; ++index)
    {
        if (array[index] == element)
            return true;

        if (array[index] > element)
            return false;
    }

    // contant time c7
    return false;

    // overall:
    // c1 + c2 + size*(c3 + c4 + c5 + c6) + c7
    // c + d*size
    // the average time will be reduced, but still the growth rate is O(n)
}

// print the elements of the array
// O(n)
void print(const int* array, size_t n)
{
    // check if the values of the input arguments are valid
    assert(array);

    std::cout << "The elements in the array are: ";

    for (size_t i = 0; i < n; ++i)
    {
        std::cout << array[i] << ' ';
    }

    std::cout << std::endl;
}


// binary search O(log(n))
// can be applied to a sorted array only (in this particular case: ascending order)

// initialy the size of the input data is n
// in the recursive call each time the size is reduced twice: n/2, n/4, n/8..., n/2^k
// the executions should stop when there is only one element or no elements at all
// n/2^k = 1 => n = 2^k => k = log(n) (base: 2)

bool isInBinary(const int* array, int startIndex, int endIndex, int element)
{
    if (startIndex > endIndex)
        return false;

    int middleIndex = (startIndex + endIndex) / 2;

    if (array[middleIndex] == element)
        return true;

    if (element < array[middleIndex])
    {
        return isInBinary(array, startIndex, middleIndex - 1, element);
    }

    // element > array[middleIndex]
    return isInBinary(array, middleIndex + 1, endIndex, element);
}

// find the number of digits in a non-negative number

// how many times does the loop run?
// 1 step: number
// 2 step: number / 10
// 3 step: (number / 10) / 10
// ...
// k step: number / 10^(k - 1)
// on the last step number / 10^(k - 1) = 1

// the size of the input is reduces on each step constant times
// O(log(n))

unsigned countDigits(unsigned number)
{
    unsigned count = 0;

    while (number > 0)
    {
        ++count;
        number = number / 10;
    }

    return count;
}

// check if all elements in an array are different

// inner loop runs 
// 1 step: n - 1 times
// 2 step: n - 2 times
// ...
// n - 1 step: 1 time
// (n - 1) + (n - 2) + (n - 3) + ... + 3 + 2 + 1
// n * (n - 1) = n^2 - n

// the if statement in the inner loop takes constant time
// all assignments, comparisons and simple arithmetic operations take constant time

// O(n^2)

bool hasDifferentElements(const int* array, size_t n)
{
    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            if (array[i] == array[j])
                return false;
        }
    }
        
    return true;
}

// how to determine the complexity of the recursive Fibonacci? 

// Lets suppose that T(n) is the time it takes the n-th number to be calculated
// Lets suppose that T(n - 1) = T(n - 2) 

// T(n) = 2 * T(n - 1) + 1 (1 for the constant time of the if statement)
// T(n) = 2 * (2 * T(n - 2) + 1) + 1 = 4 * T(n - 2) + 2 + 1
// T(n) = 4 * (2 * T(n - 3) + 1) + 2 + 1 = 8 * T(n - 3) + 4 + 2 + 1
// ...
// T(n) = 2^k * T(n - k) + 2^(k - 1) + ... + 1
// stops when n - k = 1 => k = n - 1
// T(n) = 2^(n - 1) + 2^(n - 2) + ... + 2 + 1
// T(n) = 2^n - 1

// the overall complexity is O(2^n)
// usually two recursive calls lead to exponential growth

// can this complexity be reduced?
// what if the already calculated Fibonacci numbers are stored?

int fib(int n)
{
    if (n <= 1)
        return n;

    return fib(n - 1) + fib(n - 2);
}

int main()
{
    std::cout << "5 degrees Celsius = " << convertCelsiusToFahrenheit(5) << " degrees Fahrenheit." << std::endl;

    int array[]{ 1, 2, 5, 7, 10, 14 };
    size_t size = sizeof(array) / sizeof(int);
    
    print(array, size);
    std::cout << "Is 7 in the array? " << std::boolalpha << isIn(array, size, 7) << std::endl;
    std::cout << "Is 6 in the array? " << std::boolalpha << isInSorted(array, size, 6) << std::endl;
    std::cout << "Is 11 in the array? " << std::boolalpha << isInBinary(array, 0, size, 11) << std::endl;

    std::cout << "Has the array different elements? " << std::boolalpha << hasDifferentElements(array, size) << std::endl;

    std::cout << "1234 has " << countDigits(1234) << " digits." << std::endl;

    std::cout << "The " << 7 << "th Fibonacci number is " << fib(7) << std::endl;
    
    return 0;
}
