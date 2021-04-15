#include "Order.h"

#include <cassert>
#include <cstring>

double Order::maxTotalPrice = 100;

Order::Order(const char* _name)
	: capacity(0), itemCount(0), items(nullptr)
{
	assert(_name != nullptr);
	this->name = new char[strlen(_name) + 1];
	strcpy_s(this->name, strlen(_name) + 1, _name);
}

Order::Order(Order const& other)
	: Order(other.name)
{
	capacity = other.capacity;
	itemCount = other.itemCount;

	this->items = new Item[capacity];
	for (int i = 0; i < itemCount; i++) {
		this->items[i] = other.items[i];
	}
}

Order& Order:: operator=(const Order& other) {
	if (this != &other) {

		delete[] this->name;
		this->name = new char[strlen(other.name) + 1];
		strcpy_s(this->name, strlen(other.name) + 1, other.name);

		capacity = other.capacity;
		itemCount = other.itemCount;

		delete[] this->items;
		this->items = new Item[capacity];
		for (int i = 0; i < itemCount; i++) {
			this->items[i] = other.items[i];
		}
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
	if (newName != nullptr)
	{
		delete[]this->name;

		this->name = new char[strlen(newName) + 1];
		strcpy_s(this->name, strlen(newName) + 1, newName);
	}
}

Item* Order::operator[](const char* code)
{
	for (int i = 0; i < itemCount; i++)
	{
		if (strcmp(code, items[i].getCode()) == 0)
		{
			return &items[i];
		}
	}

	return nullptr;
}

double Order::totalPrice()const {
	double price = 0;
	
	for (int i = 0; i < itemCount; i++) {
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