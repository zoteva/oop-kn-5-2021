#pragma once

class Formula
{
	public:
		virtual ~Formula() {}

		virtual void print() const = 0;
		virtual double value() const = 0;
		virtual Formula* clone() const = 0;
};