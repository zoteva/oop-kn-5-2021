#include "Magazine.h"

#include <iostream>
#include <stdexcept>

Magazine::Periodicity Magazine::getPeriodicity() const
{
	return this->mPeriod;
}

void Magazine::setPeriodicity(Periodicity period)
{
	if((int) period < 0 || (int) period> 2)
		throw std::invalid_argument("Invalid value for the period!");
	
	mPeriod = period;
}

PrintEdition* Magazine::clone() const
{
	return new Magazine(*this);
}

Magazine::Magazine(const char* name,double price,size_t year, Periodicity period)
	:PrintEdition(year,name,price)
{
	setPeriodicity(period);
}

void Magazine::printOwnData() const
{
	std::cout << "Periodicity: ";

	switch (this->mPeriod)
	{
		case Periodicity::WEEKLY:  std::cout << "Weekly" << std::endl; break;
		case Periodicity::MONTHLY: std::cout << "Monthly" << std::endl; break;
		case Periodicity::ANNUALY: std::cout << "Annually" << std::endl; break;
		
		default:
			std::cout << "Invalid periodicity!" << std::endl;
			break;
	}
}