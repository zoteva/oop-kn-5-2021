#include "Bookstore.h"

#include <cstring>
#include <iostream>

Bookstore::Bookstore(const char* _name)
{
	createDynCopy(this->mName, _name);
	// the collection of print editions is initially empty
}

void Bookstore::copyCollection(const std::vector<PrintEdition*>& otherCollection)
{
	for (size_t i = 0; i < otherCollection.size(); ++i)
	{
		// вирутуалната функция clone ще създаде копие на 
		// всяко печатно издание в other, било то книга, списание или комикс
		this->mCollection[i] = otherCollection[i]->clone();
	}
}

void Bookstore::eraseCollection()
{
	for (size_t i = 0; i < this->mCollection.size(); ++i)
	{
		delete this->mCollection[i];
	}
}

Bookstore::Bookstore(const Bookstore& other)
	: mCollection(other.mCollection.size()), mName(nullptr)
{
	copyCollection(other.mCollection);
	this->setName(other.mName);
}

Bookstore& Bookstore::operator=(const Bookstore& other)
{
	if (this != &other)
	{
		this->setName(other.mName);

		this->eraseCollection();
		this->copyCollection(other.mCollection);
	}

	return *this;
}

Bookstore::~Bookstore()
{
	this->eraseCollection();
}

const char* Bookstore::getName() const
{
	return this->mName;
}

void Bookstore::setName(const char* _name)
{
	char* buffer = nullptr;
	createDynCopy(buffer, _name);

	delete[] this->mName;
	this->mName = buffer;
}

Bookstore& Bookstore::addPrintEdition(const PrintEdition& newPE)
{
	// добавяме към колекцията динамично копие на подадения обект
	this->mCollection.push_back(newPE.clone());

	return *this;
}

size_t Bookstore::countPrintEditions() const
{
	return this->mCollection.size();
}

PrintEdition& Bookstore::getPrintEditionAt(size_t position)
{
	if (position >= mCollection.size())
		throw std::out_of_range("Index is out of range!");

	return *mCollection[position];
}

const PrintEdition& Bookstore::getPrintEditionAt(size_t position) const
{
	if (position >= mCollection.size())
		throw std::out_of_range("Index is out of range!");

	return *mCollection[position];
}

void Bookstore::print() const
{
	std::cout << "Bookstore: " << this->mName << std::endl;
	std::cout << "Collection: " << std::endl;

	for (PrintEdition* currentPE : this->mCollection)
	{
		currentPE->print();
	}
}


