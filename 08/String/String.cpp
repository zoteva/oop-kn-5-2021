#include "String.h"

#include <cstring>
#include <exception>

void String::setData(const char* newData)
{
	delete[] this->data;
	this->data = nullptr;

	if (newData != nullptr)
	{
		size_t len = strlen(newData) + 1;
		this->data = new char[len];

		strcpy_s(this->data, len, newData);
	}
}

String::String(const char* data)
{
	this->setData(data);
}

String::~String()
{
	delete[] this->data;
}

String::String(const String& other)
	: String(other.data)
{}

String& String::operator=(const String& other)
{
	if(this != &other)
	{
		setData(other.data);
	}

	return *this;
}

bool String::operator!() const
{
	return (*this == "");
}

char& String::operator[](size_t index)
{
	// дали индексът е валиден?
	if (index > strlen(this->data))
		throw std::exception("Index out of the range!");

	return this->data[index];
}

const char& String::operator[](size_t index) const
{
	if (index > strlen(this->data))
		throw std::exception("Index out of the range!");

	return this->data[index];
}

size_t String::length() const
{
	return strlen(data);
}

String& String::operator+=(const String& other)
{
	// определяме новата дължина на стринга
	size_t newLength = length() + other.length() + 1;

	// временно заделяме памет, в която да натрупаме двата стринга
	char* temp = new char[newLength];

	// копираме последователно левия и десния стринг
	strcpy_s(temp, length() + 1, this->data);
	strcpy_s(temp + length(), other.length() + 1, other.data);

	// освобождаваме паметта, с която е свързан текущия обект
	delete[] this->data;

	// свързваме указателя на текущия обект с новите данни
	this->data = temp;

	return *this;
}

// операцията + използва +=
String operator+(const String& left, const String& right)
{
	String result{ left };
	result += right;
	return result;
}

// предефиниране на операцията (), за да реализираме
// връщане на подниз от опреденена позиция с определен брой символи
String String::operator()(size_t pos, size_t len) const
{
	size_t curLength = this->length();
	
	// валидация на входните аргументи
	if(pos > curLength || !len)
		return ""; 
	// ще се включи конструкторът на класа, за да създаде необходимия обект
    // неявно преобразуване

	// изчисляване дължината на подниза
	// ако имаме низ с дължина 5 ("абвгд") и искаме да намерим подниз
	// от позиция 2 с дължина 4, 2 + 4 > 5 => можем да копираме само ел. до индекс
	// length - 1, т.е. броя символи е (length - 1) - position + 1 = length - position
	
	if(pos + len >= curLength)
		len = curLength - pos;

	char* temp = new char[len + 1];
	// копираме len наброй символа, от позиция pos в temp
	strncpy_s(temp, len + 1, this->data + pos, len);

	String res(temp);
	delete[] temp;
	
	return res;
}

// предефиниране на операциите за сравнение

// Логиката може да бъде във функциите > и ==. 
// Всички останали операции използват тях.

bool operator>(const String& left, const String& right)
{
	return strcmp(left.c_str(), right.c_str()) > 0;
}

bool operator==(const String& left, const String& right)
{
	return strcmp(left.c_str(), right.c_str()) == 0;
}

bool operator>=(const String& left, const String& right)
{
	return (left > right) || (left == right);
}

bool operator<(const String& left, const String& right)
{
	return !(left >= right);
}

bool operator<=(const String& left, const String& right)
{
	return !(left > right);
}

bool operator!=(const String& left, const String& right)
{
	return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
	out << str.c_str();
	return out;
}