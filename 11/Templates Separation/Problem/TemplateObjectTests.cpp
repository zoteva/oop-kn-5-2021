#include "TemplateObject.h"

#include <iostream>

int main()
{
	// грешка по време на компилация
	// не се открива дефиниция на конструктора TemplateObject<int>(int const&)
	
	// такава не е генерирана, защото по време на компилацията 
	// на TemplateObject.cpp файла, не е срещнат конкретния тип, който да замени Т

	TemplateObject<int> intObject(2);
	std::cout << intObject.data << std::endl;

	return 0;
}