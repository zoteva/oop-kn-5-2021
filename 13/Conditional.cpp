#include "Conditional.h"
#include <iostream>
#include <stdexcept>

Conditional::Conditional(Formula* cond, Formula* ifTrue, Formula* ifFalse)
{
	if (!cond || !ifTrue || !ifFalse)
		throw std::invalid_argument("Invalid operand has been used!");

	this->condition = cond->clone();
	this->whenTrue = ifTrue->clone();
	this->whenFalse = ifFalse->clone();
}

Conditional::Conditional(const Conditional& other)
	: condition(other.condition->clone()), whenTrue(other.whenTrue->clone()), whenFalse(other.whenFalse->clone())
{}


Conditional::~Conditional()
{
	delete this->condition;
	delete this->whenTrue;
	delete this->whenFalse;
}

Conditional& Conditional::operator=(const Conditional& other)
{
	if (this != &other)
	{
		delete this->condition;
		delete this->whenTrue;
		delete this->whenFalse;

		this->condition = other.condition->clone();
		this->whenTrue = other.whenTrue->clone();
		this->whenFalse = other.whenFalse->clone();

	}
	return *this;
}

Formula* Conditional::clone() const
{
	return new Conditional(*this);
}

void Conditional::print() const
{
	std::cout << "if (";
	condition->print();
	std::cout << ") then ";
	whenTrue->print();
	std::cout << " else ";
	whenFalse->print();
}

double Conditional::value() const
{	
	if (condition->value() == 0)
	{
		return whenFalse->value();
	}
	else
	{
		return whenTrue->value();
	}
}
