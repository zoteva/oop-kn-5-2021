#pragma once

#include "Formula.h"

// a + b, a - b, (a + b) * c
class BinaryOperation : public Formula
{
	public:
		BinaryOperation(char op, Formula* leftOp, Formula* rightOp);
		BinaryOperation(const BinaryOperation& other);
		BinaryOperation& operator=(const BinaryOperation& other);
		~BinaryOperation();

		virtual Formula* clone() const override;
		virtual void print() const override;
		virtual double value() const override;

		static bool isValidOperation(char operation);

	private:
		static const char* validOperations; // "+-*/<="

	private:
		Formula* lhs;
		Formula* rhs;
		char operation; // +, -, *, /, <, =
};
