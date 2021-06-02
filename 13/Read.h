#pragma once

#include "Formula.h"

#include <iostream>

class Read : public Formula
{
	public:
		Read()
			: data(0.0)
		{
			std::cout << "Please, enter a double value: ";
			std::cin >> this->data;
		}

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
			return new Read(*this);
		}

	private:
		double data;
};
