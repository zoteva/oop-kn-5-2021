#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <iostream>

class String
{
	public:
		String(const char* data = "");
		String(const String& other);
		String& operator=(const String& other);
		~String();

		// предефиниране на унарен оператор !
		// проверява дали текущия обект не е празен низ
		bool operator!() const;

		// предефиниране на операциите за индексиране []
		// можем да променяме стойността на посочения елемент
		char& operator[](size_t);

		// тук елементът не може да се променя
		const char& operator[](size_t) const;

		// връща дължината на стринга
		size_t length() const;

		// конкатениране на низове
		String& operator+=(const String& right);

		const char* c_str() const { return this->data; }

		// pos - начална позиция
		// len - общ брой символи
		// връщане на подниз от опреденена позиция с определен брой символи
		String operator()(size_t pos, size_t len) const;

	private:
		char* data{ nullptr };
		// size_t len{};

		// помощна член-функция, която се грижи за заделянето на памет
		void setData(const char*);
};

String operator+(const String& left, const String& right);

bool operator>(const String& left, const String& right);
bool operator>=(const String& left, const String& right);
bool operator<(const String& left, const String& right);
bool operator<=(const String& left, const String& right);

bool operator==(const String& left, const String& right);
bool operator!=(const String& left, const String& right);

std::ostream& operator<<(std::ostream& out, const String& str);

#endif // !STRING_H_INCLUDED
