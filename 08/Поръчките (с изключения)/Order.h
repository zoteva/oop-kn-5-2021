#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

#include "Item.h"

class Order 
{
	public:
		Order(const char* _name);
		Order(Order const& other);
		Order& operator=(const Order& other);
		~Order();

		void setName(const char* newName);

		const char* getName() const { return this->name; }

		Item* operator[](const char* code);
		const Item* operator[](const char* code) const;

		double totalPrice()const;

		Order& operator+=(const Item& other);

	private:
		char* name{ nullptr };

		Item* items{ nullptr };
		int itemCount{ 0 };
		int capacity{ 0 };

		static double maxTotalPrice;

	private:
		void copyItems(const Order& other);

		int findItemByCode(const char* code) const;
};

#endif // !ORDER_H_INCLUDED