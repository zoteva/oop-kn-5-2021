#include "BinaryOperation.h"

#include <iostream>
#include <stdexcept>
#include <cassert>

BinaryOperation::BinaryOperation(char op, Formula* leftOp, Formula* rightOp)
{
	if(!isValidOperation(op))
		throw std::invalid_argument("Invalid operation has been used!");

	if(!leftOp || !rightOp)
		throw std::invalid_argument("Invalid operand has been used!");

	this->operation = op;

	lhs = leftOp->clone();
	rhs = rightOp->clone();
}

BinaryOperation::BinaryOperation(const BinaryOperation& other)
	: operation(other.operation), lhs(other.lhs->clone()), rhs(other.rhs->clone())
{}

BinaryOperation& BinaryOperation::operator=(const BinaryOperation & other)
{
	if (this != &other)
	{
		delete this->lhs;
		delete this->rhs;

		this->operation = other.operation;
		this->lhs = other.lhs->clone();
		this->rhs = other.rhs->clone();
	}

	return *this;
}

BinaryOperation::~BinaryOperation()
{
	delete this->lhs;
	delete this->rhs;
}

Formula* BinaryOperation::clone() const
{
	return new BinaryOperation(*this);
}

const char* BinaryOperation::validOperations = "+-*/<=";

bool BinaryOperation::isValidOperation(char operation)
{
	// return operation == '+' || operation == '-' || operation == '*' || operation == '/' || operation == '<' || operation == '=';

	return strchr(BinaryOperation::validOperations, operation) != nullptr;
}

void BinaryOperation::print() const
{
	std::cout << '(';
	lhs->print();
	std::cout << this->operation;
	rhs->print();
	std::cout << ')';
}

double BinaryOperation::value() const
{
	double result = 0.0;

	switch (this->operation)
	{
		case '+': 
			result = lhs->value() + rhs->value(); break;

		case '-': 
			result = lhs->value() - rhs->value(); break;

		case '*': 
			result = lhs->value() * rhs->value(); break;

		case '/': 
			result = lhs->value() / rhs->value(); break;

		case '<': 
			result = (lhs->value() < rhs->value())? 1.0 : 0.0; break;
			// !!! comparison of two double values
		case '=': 
			result = lhs->value() == rhs->value(); break;

		default:
			assert("Invalid operation" && false);
	}

	return result;
}
