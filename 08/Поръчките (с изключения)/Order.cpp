#include "Order.h"

#include <cassert>
#include <cstring>
#include <exception>

double Order::maxTotalPrice = 100;

void Order::copyItems(const Order& other)
{
	this->capacity = other.capacity;
	this->itemCount = other.itemCount;

	this->items = new Item[this->capacity];
	for (int i = 0; i < this->itemCount; i++)
	{
		this->items[i] = other.items[i];
	}
}

int Order::findItemByCode(const char* code) const
{
	for (int i = 0; i < itemCount; i++)
	{
		if (strcmp(code, items[i].getCode()) == 0)
		{
			return i;
		}
	}

	return -1;
}

Order::Order(const char* _name)
	// : capacity(0), itemCount(0), items(nullptr)
{
	this->setName(_name);
}

Order::Order(Order const& other)
{
	this->setName(other.name);
	this->copyItems(other);
}

Order& Order:: operator=(const Order& other) 
{
	if (this != &other) 
	{
		this->setName(other.name);

		delete[] this->items;
		this->copyItems(other);
	}

	return *this;
}

Order::~Order()
{
	delete[] this->name;
	delete[] this->items;
}

void Order::setName(const char* newName)
{
	if (newName == nullptr)
		throw std::exception("Invalid name!");

	size_t nameLen = strlen(newName);
	if (nameLen == 0)
		throw std::exception("Empty name!");

	delete[] this->name;

	this->name = new char[nameLen + 1];
	strcpy_s(this->name, nameLen + 1, newName);
}

Item* Order::operator[](const char* code)
{
	int index = findItemByCode(code);

	if(index == -1)
		return nullptr;

	return &this->items[index];
}

const Item* Order::operator[](const char* code) const
{
	int index = findItemByCode(code);

	if (index == -1)
		return nullptr;

	return &this->items[index];
}

double Order::totalPrice()const 
{
	double price = 0;
	
	for (int i = 0; i < itemCount; i++) 
	{
		price += this->items[i].getPrice();
	}
	
	return price;
}

Order& Order::operator+=(const Item& other)
{
	if (this->totalPrice() + other.getPrice() > maxTotalPrice)
		return *this;

	if (this->itemCount < this->capacity)
	{
		this->items[++this->itemCount] = other;
	}
	else
	{
		Item* temp = new Item[this->capacity + 4];
		for (int i = 0; i < this->itemCount; i++)
			temp[i] = this->items[i];
	
		delete[] this->items;
		
		this->items = temp;
		
		this->capacity += 4;
		this->items[++this->itemCount] = other;
	}

	return *this;
}