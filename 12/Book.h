#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include "PrintEdition.h"
#include "CStringFunctions.h"

// виртуален базов клас
class Book : public virtual PrintEdition
{
public:
	Book(size_t _year, const char* _name, double _price, const char* _author);
	Book(const Book& other);
	Book& operator=(const Book& other);
	virtual ~Book();

	void setAuthor(const char* _author);
	const char* getAuthor() const;

	virtual PrintEdition* clone() const override;

protected:
	// дефиниране на чисто-виртуалната функция от базовия клас
	virtual void printOwnData() const;

private:
	char* mAuthor;
};

#endif // !BOOK_H_INCLUDED






