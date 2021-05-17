#ifndef MAGAZINE_H_INCLUDED
#define MAGAZINE_H_INCLUDED

#include "PrintEdition.h"

class Magazine : public virtual PrintEdition {
public:

	enum class Periodicity { WEEKLY, MONTHLY, ANNUALY };

	// няма заделяне на допълнителни ресурси в конструктора на класа
	// => няма нужда да дефинираме останалите функции от rule of 3 (or 5)
	Magazine(const char* name, double price, size_t year, Periodicity period);

	Periodicity getPeriodicity() const;
	void setPeriodicity(Periodicity period);

	virtual PrintEdition* clone() const override;

protected:
	virtual void printOwnData() const override;

private:
	Periodicity mPeriod;
};

#endif // !MAGAZINE_H_INCLUDED