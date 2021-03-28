#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>


struct Product
{
	double price{ 0 };
	int quantity{ 0 };
	char* name{ nullptr };

	void initializeProduct(const char* name, double price, int quantity);
	void freeProduct();

	void writeToBinary(std::fstream&) const;
	bool readFromBinary(std::fstream&);

	void print() const;
};

void Product::initializeProduct(const char* newName, double newPrice, int newQuantity)
{
	// when the object is already initialized
	// the name holds the adress of dynamic memory

	// before allocating new block of memory
	// the old one should be cleared
	delete[] this->name;

	this->name = new char[strlen(newName) + 1];
	strcpy(this->name, newName);

	this->price = newPrice;

	this->quantity = newQuantity;
}

void Product::freeProduct()
{
	delete[] this->name;
	this->name = nullptr;

	this->quantity = 0;
	this->price = 0;
}

void Product::writeToBinary(std::fstream& file) const
{
	if (!file)
	{
		std::cout << "The state of the stream is not good! Write operation cannot be performed!" << std::endl;
		return;
	}

	file.write(reinterpret_cast<const char*>(&price), sizeof(price));
	file.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));

	// store the length of the name first, then the name itself
	size_t nameLen = strlen(name);
	file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
	file.write(name, nameLen);
}

bool Product::readFromBinary(std::fstream& file)
{
	if (!file)
	{
		std::cout << "The state of the file is not good! Clear has been performed before reading!";
		file.clear();
	}
		
	double newPrice = 0;
	file.read(reinterpret_cast<char*>(&newPrice), sizeof(newPrice));

	if (file && file.gcount() == sizeof(price))
	{
		int newQuantity = 0;
		file.read(reinterpret_cast<char*>(&newQuantity), sizeof(newQuantity));

		if (file && file.gcount() == sizeof(newQuantity))
		{
			size_t nameLen = 0;
			file.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));

			if (file && file.gcount() == sizeof(nameLen))
			{
				char* newName = new char[nameLen + 1];
				file.read(newName, nameLen);

				newName[nameLen] = '\0';

				if (file && file.gcount() == nameLen)
				{
					// change the current object
					//this->initializeProduct(newName, newPrice, newQuantity);
					delete[] this->name;

					this->name = newName;
					this->price = newPrice;
					this->quantity = newQuantity;
				}
				else
				{
					// the last operation has failed, but dynamic memory has been allocated
					delete[] newName;
				}
			}

			return true;
		}
	}

	return false;
}

void Product::print() const
{
	// cannot change the current object in a const function
	// this->price = 2;

	std::cout << "Name: " << name << std::endl;
	std::cout << "Price: " << price << std::endl;
	std::cout << "Quantity: " << quantity << std::endl;
}

void function(const Product& p)
{
	p.print();
}

void storeProductsInBinaryFile(const char* fileName, const Product* products, size_t count)
{
	std::fstream file(fileName, std::ios::out | std::ios::ate | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "The file " << fileName << " cannot be opened!" << std::endl;
		return;
	}

	// append the content of the array to the file
	for (size_t index = 0; index < count; ++index)
	{
		products[index].writeToBinary(file);
	}

	file.close();
}

void showFroductsInBinaryFile(const char* fileName)
{
	std::fstream file(fileName, std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "The file " << fileName << " cannot be opened!" << std::endl;
		return;
	}

	file.seekg(0, std::ios::beg);
	while (file)
	{
		Product currentProduct;
		if (currentProduct.readFromBinary(file))
		{
			currentProduct.print();
		}

		currentProduct.freeProduct();
	}

	file.close();
}

void freeProducts(Product* products, size_t count)
{
	for (size_t index = 0; index < count; ++index)
	{
		products[index].freeProduct();
	}
}

int main()
{
	Product gum{};
	gum.initializeProduct("gum", 1.20, 10);
	gum.print();
	gum.freeProduct();
	
	//Product products[3];
	//products[0].initializeProduct("Milk", 2.50, 5);
	//products[1].initializeProduct("Chocolate", 4.50, 2);
	//products[2].initializeProduct("Mint Tea", 1.50, 10);

	//storeProductsInBinaryFile("Products.bin", products, 3);

	//freeProducts(products, 3);

	showFroductsInBinaryFile("Products.bin");

	return 0;
}