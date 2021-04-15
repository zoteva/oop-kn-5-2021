#define _CRT_SECURE_NO_WARNINGS

#include "Item.h"

#include <cassert>
#include <cstring>

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
	assert(isValid(_code));
	strcpy(this->code, _code);
			
	assert(_name != nullptr);
	this->name = new char[strlen(_name) + 1];
	strcpy_s(this->name, strlen(_name) + 1, _name);

	assert(_price >= 0);
	this->price = _price;
}

Item::Item(const Item& other)
	: Item(other.code, other.name, other.price)
{}

Item& Item::operator=(const Item& other)
{
	if (this != &other)
	{
		strcpy(this->code, other.code);

		delete[] this->name;
		this->name = new char[strlen(other.name) + 1];
		strcpy_s(this->name, strlen(other.name) + 1, other.name);

		this->price = other.price;
	}

	return *this;
}

Item::~Item(){
	delete[] name;
}

void Item::setCode(const char* newCode)
{
	if(isValid(newCode))
	{
		strcpy(this->code, newCode);
	}
}

void Item::setName(const char* newName)
{
	delete[] this->name;
	this->name = new char[strlen(newName) + 1];
	strcpy_s(this->name, strlen(newName) + 1, newName);
}

void Item::setPrice(double newPrice)
{
	if(newPrice>=0)
	{
		this->price = newPrice;
	}
	else
	{
		this->price = 0;
	}
}

bool Item::operator==(const Item& other)const {
	return strcmp(this->code, other.code) == 0;
}
