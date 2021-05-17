#ifndef COMICS_H_INCLUDED
#define COMICS_H_INCLUDED

#include "Book.h"
#include "Magazine.h"

class Comics :
    public Book, public Magazine
{
public:
    // 1) задължително обръщение към конструктора на виртуалния базов клас,
    // 2) последвано от обръщение към конструкторите на преките предшественици
    Comics(size_t _year, const char* _name, double _price, const char* _author, Magazine::Periodicity _period) :
        PrintEdition(_year, _name, _price),
        Book(_year, _name, _price, _author),
        Magazine(_name, _price, _year, _period)
    {}

    virtual PrintEdition* clone() const override
    {
        return new Comics(*this);
    }

protected:
    virtual void printOwnData() const override
    {
        Book::printOwnData();
        Magazine::printOwnData();
    }
};

#endif // !COMICS_H_INCLUDED


