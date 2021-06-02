#pragma once

#include "Formula.h"

class Conditional : public Formula
{
	public:
		Conditional(Formula* cond, Formula* ifTrue, Formula* ifFalse);
		Conditional(const Conditional& other);
		Conditional& operator=(const Conditional& other);
		~Conditional();

		virtual Formula* clone() const override;
		virtual void print() const override;
		virtual double value() const override;

	private:
		Formula* condition;
		Formula* whenTrue;
		Formula* whenFalse;
};