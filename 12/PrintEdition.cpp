#include "PrintEdition.h"

#include <exception>
#include <iostream>

PrintEdition::PrintEdition(size_t year, const char* name, double price)
	: mName(nullptr)
{
	setYear(year);
	setName(name);
	setPrice(price);
}

PrintEdition::~PrintEdition()
{
	//std::cout << "~PrintEdition" <<std::endl;
	delete[] this->mName;
}

PrintEdition::PrintEdition(const PrintEdition& other)
	: PrintEdition(other.mYear, other.mName, other.mPrice)
{}

PrintEdition::PrintEdition(PrintEdition&& other) noexcept
{
	this->mYear = other.mYear;
	this->mName = other.mName;
	this->mPrice = other.mPrice;

	other.mName = nullptr;
}

PrintEdition& PrintEdition::operator=(const PrintEdition& other)
{
	if (this != &other) 
	{
		setYear(other.mYear);
		setName(other.mName);
		setPrice(other.mPrice);
	}

	return *this;
}

PrintEdition& PrintEdition::operator=(PrintEdition&& other) noexcept
{
	if (this != &other) {

		this->mYear = other.mYear;
	
		delete[] this->mName;
		this->mName = other.mName;
		
		this->mPrice = other.mPrice;

		other.mName = nullptr;
	}

	return *this;
}

void PrintEdition::setYear(size_t year)
{
	this->mYear = year;
}

void PrintEdition::setName(const char* name)
{
	char* buffer = nullptr;
	createDynCopy(buffer, name);

	delete[] this->mName;
	this->mName = buffer;
}

void PrintEdition::setPrice(double price)
{
	if (price < 0)
		throw std::invalid_argument("Invalid value for the price!");

	this->mPrice = price;
}

size_t PrintEdition::getYear() const
{
	return this->mYear;
}

const char* PrintEdition::getName() const
{
	return this->mName;
}

double  PrintEdition::getPrice() const
{
	return this->mPrice;
}

void PrintEdition::print() const
{
	// извеждаме общите член-данни
	// всеки производен клас трябва да предефинира 
	// чисто-виртуалната функция printOwnData, 
	// за да бъдат изведени и собствените му такива

	std::cout << "Name: " << this->mName << std::endl;
	std::cout << "Year: " << this->mYear << std::endl;
	std::cout << "Price: " << this->mPrice << std::endl;

	this->printOwnData();
}