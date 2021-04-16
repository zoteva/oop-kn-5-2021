#define _CRT_SECURE_NO_WARNINGS

#include "Item.h"

#include <cassert>
#include <cstring>

#include <exception>
#include <stdexcept>

bool isValid(const char* _code)
{
	if (_code == nullptr)
		return false;

	if (strlen(_code) != 5)
		return false;

	for (int i = 0; i < 5; i++)
		if (_code[i] < '0' || _code[i] > '9')
			return false;

	return true;
}

Item::Item(const char* _code, const char* _name, double _price)
{
	//if (!isValid(_code))
	//	throw std::exception("Invalid code!");

	//strcpy(this->code, _code);
	
	//if (_price < 0)
	//	throw std::exception("Invalid price!");

	//this->price = _price;

	//if (_name == nullptr)
	//	throw std::exception("Invalid name!");

	//this->name = new char[strlen(_name) + 1];
	//strcpy_s(this->name, strlen(_name) + 1, _name);

	try
	{
		this->setCode(_code);
		this->setName(_name);
		this->setPrice(_price);
	}
	catch (const std::exception& ex)
	{
		delete[] this->name;

		throw;
	}
}

Item::Item(const Item& other)
	: Item(other.code, other.name, other.price)
{}

Item& Item::operator=(const Item& other)
{
	if (this != &other)
	{
		this->setCode(other.code);
		this->setName(other.name);
		this->setPrice(other.price);
	}

	return *this;
}

Item::~Item(){
	delete[] name;
}

void Item::setCode(const char* newCode)
{
	if (!isValid(newCode))
		throw std::exception("Invalid code!");

	strcpy(this->code, newCode);
}

void Item::setName(const char* newName)
{ 
	if (newName == nullptr)
		throw std::exception("Invalid name!");

	size_t nameLen = strlen(newName);
	if(nameLen == 0)
		throw std::exception("Empty name!");

	delete[] this->name;

	this->name = new char[nameLen + 1];
	strcpy_s(this->name, nameLen + 1, newName);
}

void Item::setPrice(double newPrice)
{
	if (newPrice < 0)
		throw std::exception("Invalid price!");

	this->price = newPrice;
}

bool Item::operator==(const Item& other)const {
	return strcmp(this->code, other.code) == 0;
}
