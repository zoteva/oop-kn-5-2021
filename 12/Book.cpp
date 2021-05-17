#include "Book.h"

#include <iostream>

// ����� ���� �� ����� �� ����������� �� ����-�����!
Book::Book(size_t _year, const char* _name, double _price, const char* _author) 
	: PrintEdition(_year, _name, _price)
{
	createDynCopy(this->mAuthor, _author);
}

// ������ ���� ����������� ����-�����
Book::~Book()
{
	delete[] this->mAuthor;
}

// ��������� ��� ������� (��� ���� �����������) �� ������� ����,
// ����� �� ������������ ����������� ����-�����

Book::Book(const Book& other)
	: PrintEdition(other)
{
	createDynCopy(this->mAuthor, other.mAuthor);
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		// ��������� ��� ������������ ������� �� ����������� �� ������� ����,
		// �� �� �������� �������� ����������� ����-�����

		PrintEdition::operator=(other);
		
		this->setAuthor(other.mAuthor);
	}

	return *this;
}

void Book::setAuthor(const char* _author) 
{ 
	char* buffer = nullptr;
	createDynCopy(buffer, _author);

	delete[] this->mAuthor;
	this->mAuthor = buffer;
}

const char* Book::getAuthor() const
{ 
	return this->mAuthor; 
}

PrintEdition* Book::clone() const
{
	return new Book(*this);
}

void Book::printOwnData() const
{
	std::cout << "Author: " << this->mAuthor << std::endl;
}


