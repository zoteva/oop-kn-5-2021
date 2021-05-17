#ifndef PRINTEDITION_H_INCLUDED
#define PRINTEDITION_H_INCLUDED

#include "CStringFunctions.h"

class PrintEdition 
{
	public:
		PrintEdition(size_t _year, const char* _name, double _price);

		PrintEdition(const PrintEdition& other);
		PrintEdition(PrintEdition&& other) noexcept;
		PrintEdition& operator=(const PrintEdition& other);
		PrintEdition& operator=(PrintEdition&& other) noexcept;
		// ВАЖНО!
		virtual ~PrintEdition();

		void setYear(size_t year);
		void setName(const char* name);
		void setPrice(double price);

		size_t getYear() const;
		const char* getName() const;
		double getPrice() const;

		// няма да бъде пренаписвана в производните класове
		// разчита на виртуалната функция printOwnData,
		// за да изведе коректна информация в производните класове
		void print() const;

		// чисто-виртуална функция, с помощта на която ще 
		// можем да правим динамични копия на обекти от производните класове
		virtual PrintEdition* clone() const = 0;

	protected:
		// чисто виртуална функция => класът е абстрактен
		// от този клас не могат да се създават обекти,
		// но можем да използване PrintEdition* и PrintEdition&

		// трябва да се дефинира в производните класове,
		// в противен случай те също ще бъдат абстрактни
		virtual void printOwnData() const = 0;

	private:
		size_t mYear;
		char* mName;
		double mPrice;
};


#endif // !PRINTEDITION_H_INCLUDED

