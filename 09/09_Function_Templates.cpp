#include "../09/ComplexNumbers (Operators overloading)/ComplexNumber.h"

#include <cstring>
#include <iostream>


// FUNCTION TEMPLATES

// find the position of the min element in a given array of integers
int findIndexOfMinElement(int* arr, int n)
{
    int indexMin = 0;
    for(int i = 1; i < n; ++i)
    {
        if(arr[i] < arr[indexMin])
        {
            indexMin = i;
        }
    }

    return indexMin;
}

// how to transfer this into a template of a function?
// int -> T, but not every int! Be careful of the meaning...
template <typename T>
int findIndexOfMin(T* arr, int n)
{
    int indexMin = 0;
    for(int i = 1; i < n; ++i)
    {
        // operator < should be defined for the type T
        // what happens if the relation < is changed with something else?
        if(arr[i] < arr[indexMin])
        {
            indexMin = i;
        }
    }

    return indexMin;
}

// <: int x int -> bool (true, false)
// we can use any function that compares two elements and the result is a boolean constant...
// how?
// the function that compares the elements of the array should be passed as an argument

// T might also be a class type, better pass the arguments by const reference, not by value...
template <typename T>
int findIndexOfExtremum(T* arr, int n, bool (*compare)(T, T))
{
    int index = 0;
    for(int i = 1; i < n; ++i)
    {
        if(compare(arr[i], arr[index]))
        {
            index = i;
        }
    }

    return index;
}

// definitions of functions for comparison of the elements in an integer array
bool lessThan(int a, int b)
{
    return a < b;
}

bool greaterThan(int a, int b)
{
    return a > b;
}

template <typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

// sort the elements of an array
void sortIntAsc(int* arr, int n)
{
    for(int i = 0; i < n; ++i)
    {
        // identify the subarray where the min element will be sought
        // which is the start position, how many are the elements?
        int indexMin = findIndexOfMinElement(arr + i, n - i);

        // do not forget the offset...
        swap(arr[i], arr[i + indexMin]);
    }
}

// sort, transformed to a template
template <typename T>
void sortAsc(T* arr, int n)
{
    for(int i = 0; i < n; ++i)
    {
        int indexMin = findIndexOfMin(arr + i, n - i);
        swap(arr[i], arr[i + indexMin]);
    }
}

// what if the way the elements should be compared is different?
template <typename T>
void sort(T* arr, int n, bool (* compare)(T, T))
{
    for(int i = 0; i < n; ++i)
    {
        int indexMin = findIndexOfExtremum(arr + i, n - i, compare);
        swap(arr[i], arr[i + indexMin]);
    }
}

// print the elements of the array
template <typename T>
void print(T* arr, int n)
{
    for(int i = 0; i < n; ++i)
    {
        // operator << should be defined for the type T
        std::cout << arr[i] << ' ';
    }

    std::cout << std::endl;
}

// specialization for the type char
void print(char* str, size_t n)
{
    std::cout << str << std::endl;
}

// T -> ComplexNumber
// U -> double, ComplexNumber
template<typename T, typename U>
U sum(const T& a, const U& b)
{
    U result = a + b;
    return result;
}

int main()
{
    const int n = 6;
    int arr[] = {5, 0, 1, 1, 4, 7};
    std::cout << "Array: ";
    print(arr, n);

    std::cout << "Index of the min element: " << findIndexOfMin(arr, n) << std::endl;
    std::cout << "Index of the max element: " << findIndexOfExtremum(arr, n, greaterThan) << std::endl;

    sort(arr, n, greaterThan);
    print(arr, n);

    char str[] = "abcd";
    print(str, strlen(str));

    ComplexNumber x{ 5, 2 };
    double y = 7;

    std::cout << sum(y, x) << std::endl;

    //const int cnN = 3;
    //ComplexNumber cnArr[] = { {5, 3}, {2, 5}, {1, 0} };

    //// ComplexNumber does not define operator <, error!
    //int indexOfMin = findIndexOfMin(cnArr, cnN);
    //std::cout << cnArr[indexOfMin] << std::endl;

    return 0;
}
