#include <iostream>
#include <cstring>

class Employee
{
	public:
		Employee() = default;
		Employee(const char* name, const char* position, double salary);

		void setName(const char* newName);
		void setPosition(const char* newPosition);
		void setSalary(double newSalary);

		double getSalary() const;
		const char* getName() const;
		const char* getPosition() const;

		void print() const;
		
	private:	
		char name[20]{};
		char position[20]{};
		double salary{ 610 };

};

Employee::Employee(const char* name, const char* position, double salary)
{
	this->setName(name);
	this->setPosition(position);
	this->setSalary(salary);
}

void Employee::setName(const char* newName)
{
	if (newName == nullptr || strlen(newName) >= 20)
		return;

	strcpy_s(this->name, 20, newName);
}

void Employee::setPosition(const char* newPosition)
{
	if (newPosition == nullptr || strlen(newPosition) >= 20)
		return;

	strcpy_s(this->position, 20, newPosition);
}

void Employee::setSalary(double newSalary)
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

void Employee::print() const
{
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Position: " << this->position << std::endl;
	std::cout << "Salary: " << this->salary << std::endl;
}

double Employee::getSalary() const
{
	return this->salary;
}

const char* Employee::getName() const
{
	return this->name;
}

const char* Employee::getPosition() const
{
	return this->position;
}

int main()
{
	Employee employees[10]{ {"Me", "Teacher", 1300}, {"You", "Software developer", 2500} };
	employees[5].print();

	//Employee me{ "Me", "Teacher", 1300 };

	////me.setName("Me");
	////me.setPosition("Teacher");
	////me.setSalary(400);

	//me.print();

	//const char* name = me.getName();
	////strcpy(name, "Gosho");
	////me.print();

	//Employee you{};
	//you.setName("You");
	//you.setPosition("Programmer");
	//you.setSalary(2500);

	//you.print();

	return 0;
}