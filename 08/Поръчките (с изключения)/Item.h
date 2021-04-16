#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

class Item
{
	public:
		Item() = default;
		Item(const char* _code, const char* _name, double _price);
		Item(const Item& other);
		Item& operator=(const Item& oher);
		~Item();

		const char* getCode() const { return this->code; }
		const char* getName() const { return this->name; }
		double getPrice() const { return this->price; }

		void setCode(const char* newCode);
		void setName(const char* newName);
		void setPrice(double newSalary);

		bool operator==(const Item& other) const;

	private:
		char code[6]{};
		char* name{ nullptr };
		double price{ 0 };
};


#endif // !ITEM_H_INCLUDED
