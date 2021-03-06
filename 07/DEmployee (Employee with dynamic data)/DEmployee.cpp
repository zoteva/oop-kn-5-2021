#include "CStringFunctions.h"
#include "DEmployee.h"

#include <cstring>
#include <iostream>

DEmployee::DEmployee(const char* newName, const char* newPosition, double newSalary)
{
	createDynCopy(this->name, newName);
	createDynCopy(this->position, newPosition);

	this->setSalary(newSalary);
}

DEmployee::DEmployee(const DEmployee& other)
	: DEmployee(other.name, other.position, other.salary)
{}

DEmployee::DEmployee(DEmployee&& other) noexcept
	: name(other.name), position(other.position), salary(other.salary)
{
	other.name = nullptr;
	other.position = nullptr;
}

DEmployee& DEmployee::operator=(DEmployee&& other) noexcept
{
	if (this != &other)
	{
		delete[] this->name;
		delete[] this->position;

		this->name = other.name;
		this->position = other.position;
		this->salary = other.salary;

		other.name = nullptr;
		other.position = nullptr;
	}

	return *this;
}

void DEmployee::swap(DEmployee& other)
{
	std::swap(this->name, other.name);
	std::swap(this->position, other.position);
	std::swap(this->salary, other.salary);
}

DEmployee& DEmployee::operator=(const DEmployee& other)
{
	DEmployee temp{ other };
	this->swap(temp);
	return *this;

	//if (this != &other)
	//{
	//	this->setName(other.name);
	//	this->setPosition(other.position);
	//	this->setSalary(other.salary);
	//}
	//
	//return *this;
}

DEmployee::~DEmployee()
{
	// the dynamic memory allocated in the constructor
	// should be cleared when the object goes out of scope
	delete[] this->name;
	delete[] this->position;
}

const char* DEmployee::getName() const
{
	return this->name;
}

const char* DEmployee::getPosition() const
{
	return this->position;
}

double DEmployee::getSalary() const
{
	return this->salary;
}

void DEmployee::setName(const char* newName)
{
	// the current object has already been linked to some dynamic memory in the constructor
	// clear the previously allocated memory, then the pointer this->name can be linked 
	// new dynamic memory, a dynamic copy of the input argument
	delete[] this->name;
	createDynCopy(this->name, newName);
}

void DEmployee::setPosition(const char* newPosition)
{
	delete[] this->position;
	createDynCopy(this->position, newPosition);
}

void DEmployee::setSalary(double newSalary)
{
	if (newSalary >= 610 && newSalary <= 10000)
	{
		this->salary = newSalary;
	}
	else if (newSalary < 610)
	{
		this->salary = 610;
	}
	else
	{
		this->salary = 10000;
	}
}

void DEmployee::print() const
{
	std::cout << "Name: " << (this->name? this->name : "") << std::endl;
	std::cout << "Position: " << (this->position? this->position : "") << std::endl;
	std::cout << "Salary: " << this->salary << std::endl;
}