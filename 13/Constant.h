#pragma once

#include "Formula.h"

#include <iostream>

class Constant : public Formula
{
	public:
		Constant(double constValue) 
			: data(constValue) 
		{}

		virtual void print() const override
		{
			std::cout << this->data;
		}

		virtual double value() const override
		{
			return this->data;
		}

		virtual Formula* clone() const override
		{
			return new Constant(*this);
		}

	private:
		const double data;
};
