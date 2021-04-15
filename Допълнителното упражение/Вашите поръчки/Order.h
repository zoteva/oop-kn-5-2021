#pragma once
#include "Item.h"

class Order {
private:
	char* name;

	Item* items;
	int itemCount;
	int capacity;

	static double maxTotalPrice;

public:
	Order(const char* _name);
	Order(Order const& other);
	Order& operator=(const Order& other);
	~Order();
	
	void setName(const char* newName);
	
	const char* getName() const{
		return this->name;
	}

	Item* operator[](const char* code);
	const Item* operator[](const char* code) const;

	double totalPrice()const;

	Order& operator+=(const Item& other);
};