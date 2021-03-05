#include <iostream>
#include <iomanip>

const size_t nameMaxLength = 20;
const size_t positionMaxLength = 20;
const size_t maxWorkExperience = 40;

struct Employee
{
	size_t id{ 0 };
	char name[nameMaxLength]{};
	char position[positionMaxLength]{};
	unsigned int workExperience{ 0 };
	double wage{ 0.0 };
};

void readEmployee(Employee& employee)
{
	// move to functions, check for correctness
	std::cout << "ID: ";
	std::cin >> employee.id;
	// why do we need this?
	std::cin.ignore();

	std::cout << "Name: ";
	std::cin.getline(employee.name, nameMaxLength);

	std::cout << "Position: ";
	std::cin.getline(employee.position, positionMaxLength);

	// Lets suppose that the experience is in the range [0; 40]
	std::cout << "Work experience [1; " << maxWorkExperience << "]: ";
	do
	{
		std::cin >> employee.workExperience;

		if (!std::cin)
		{
			std::cin.clear();
		}

		// ignore what is left in the buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (employee.workExperience < 1 || employee.workExperience > maxWorkExperience);

	// some validation of the input is necessary here
	std::cout << "Wage: ";
	std::cin >> employee.wage;
}

void printEmployee(const Employee& employee)
{
	std::cout << std::setw(5) << employee.id
		<< std::setw(20) << employee.name
		<< std::setw(20) << employee.position
		<< std::setw(10) << employee.workExperience
		<< std::setw(10) << std::setiosflags(std::ios::fixed) << std::setprecision(2) << employee.wage << std::endl;
}

void simpleTests()
{
	Employee e{};

	std::cout << "Size of Employee: " << sizeof(Employee) << std::endl;

	// cannot read an employee directly
	//std::cin >> e;

	readEmployee(e);
	printEmployee(e);

	// how to define a pointer to a structure variable?
	Employee* ptrEmployee = &e;

	// how to access data members using the pointer?
	ptrEmployee->wage += 20;
	// equavalent to 
	(*ptrEmployee).wage -= 20;

	// what will happen if the structure variable is copied?
	Employee cloning = e;
	std::cout << "-- The cloning --" << std::endl;
	printEmployee(cloning);

	// what if we try to change the copy? 
	// what will happen to the original?
	cloning.workExperience += 1;

	std::cout << "-- The changed cloning --" << std::endl;
	printEmployee(cloning);

	std::cout << "-- The original --" << std::endl;
	printEmployee(e);
}

// find the most experienced employee
int findMostExperiencedEmployee(const Employee* employees, size_t count)
{
	if(!employees || !count)
		return -1;

	size_t indexMostExperienced = 0;

	for (size_t currentIndex = 1; currentIndex < count; ++currentIndex)
	{
		if (employees[indexMostExperienced].workExperience < employees[currentIndex].workExperience)
		{
			indexMostExperienced = currentIndex;
		}
	}

	return indexMostExperienced;
}

// sort the employees by workexperience in descending order
void sort(Employee* employees, size_t count)
{
	for (size_t index = 0; index < count - 1; ++index)
	{
		// search in the rest of the array without the first element
		size_t indexMostExperienced = findMostExperiencedEmployee(employees + index, count - index);

		// in order to get the index of this element in the bigger (original) array
		indexMostExperienced += index;

		std::swap(employees[indexMostExperienced], employees[index]);
	}
}

// what if we use an additional array of pointers?
// ascending order, bubble sort, array of pointers
void sort(Employee** pEmployees, size_t count)
{
	for (size_t i = 0; i < count - 1; ++i)
	{
		for (size_t j = i + 1; j < count; ++j)
		{
			if (pEmployees[i]->workExperience > pEmployees[j]->workExperience)
			{
				std::swap(pEmployees[i], pEmployees[j]);
			}
		}
	}
}

int main()
{
	//simpleTests();

	Employee employees[10];
	Employee* pEmployees[10]{ nullptr };

	std::cout << "Number of employees? ";
	size_t numberOfEmployees = 0;
	std::cin >> numberOfEmployees;

	for (size_t i = 0; i < numberOfEmployees; ++i)
	{
		readEmployee(employees[i]);
		pEmployees[i] = &employees[i];
	}

	size_t indexMostExperienced = findMostExperiencedEmployee(employees, numberOfEmployees);
	std::cout << "The most experienced employee is: " << std::endl;
	printEmployee(employees[indexMostExperienced]);

	std::cout << "\n-- Sorted employees --\n";
	sort(pEmployees, numberOfEmployees);

	for (size_t i = 0; i < numberOfEmployees; ++i)
	{
		printEmployee(*pEmployees[i]);
	}

	return 0;
}
