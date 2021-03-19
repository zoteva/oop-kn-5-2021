#include <cassert>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>

const size_t maxLength = 20;

struct Employee
{
	size_t id{ 0 };
	char name[maxLength]{};
	char position[maxLength]{};
	unsigned int workExperience{ 0 };
	double wage{ 0.0 };
};

// Let the file has the following format
// ID	name	position	workExperience	wage
// all values are separated by a tab, the row ends in a new line
// what have to be changed here if the file format is:
// ID, name, position, workExperience, wage \newline?

bool readEmployee(std::ifstream& inputFile, Employee& employee)
{
	// the file cannot be read 
	if (!inputFile) return false;

	size_t id{ 0 };
	inputFile >> id;
	inputFile.ignore(1, '\t');

	char name[maxLength]{};
	inputFile.getline(name, maxLength, '\t');

	char position[maxLength]{};
	inputFile.getline(position, maxLength, '\t');
	
	unsigned workExperience{ 0 };
	inputFile >> workExperience;
	
	double wage{ 0 };
	inputFile >> wage;

	if (inputFile)
	{
		employee.id = id;
		strcpy_s(employee.name, maxLength, name);
		strcpy_s(employee.position, maxLength, position);
		employee.workExperience = workExperience;
		employee.wage = wage;

		return true;
	}
	else
	{
		if (inputFile.eof())
		{
			std::cout << "End of the file reached!" << std::endl;
		}
		else
		{
			inputFile.clear();

			// ignore the rest of the line
			// the read has failed
			while (inputFile.get() != '\n');
		}

		return false;
	}	
}

// save an employee in a text file, 
// the employee fields are separated by tabs
bool printEmployee(std::ofstream& outputFile, const Employee& employee)
{
	if (!outputFile) return false;

	outputFile << employee.id << '\t' << employee.name << '\t' << employee.position << '\t'
		<< employee.workExperience << '\t' << employee.wage << std::endl;

	return outputFile.good();
}

// show the employee data on the standard output
void showInfo(const Employee& employee)
{
	std::cout << std::setw(5) << employee.id
		<< std::setw(20) << employee.name
		<< std::setw(20) << employee.position
		<< std::setw(10) << employee.workExperience
		<< std::setw(10) << std::setiosflags(std::ios::fixed) << std::setprecision(2) << employee.wage << std::endl;
}

void showFileEmployeesContent(const char* inputFileName)
{
	std::ifstream inputFile(inputFileName, std::ios::in);

	if (!inputFile.is_open())
	{
		std::cout << "The input file cannot be used! Error occurred while opening...." << std::endl;
		return;
	}

	Employee employee{};
	while (inputFile)
	{
		if (readEmployee(inputFile, employee))
		{
			showInfo(employee);
		}
	}

	inputFile.close();
}

using Predicate = bool (*) (const Employee&);

void filterEmployees(const char* inputFileName, const char* resultingFileName, Predicate predicate)
{
	std::ifstream inputFile(inputFileName, std::ios::in);

	if (!inputFile.is_open())
	{
		std::cout << "The input file cannot be used! Error occurred while opening...." << std::endl;
		return;
	}

	// save only those employees for which the predicate is evaluated as true
	std::ofstream outputFile(resultingFileName, std::ios::out);

	if (!outputFile.is_open())
	{
		std::cout << "The output file cannot be used! Error occurred while opening...." << std::endl;
		return;
	}

	Employee employee{};
	while (inputFile)
	{
		if (readEmployee(inputFile, employee))
		{
			if (predicate(employee))
			{
				printEmployee(outputFile, employee);
			}
		}
	}

	// close does not clear the state of the input stream
	inputFile.clear();
	inputFile.close();

	outputFile.close();
}

bool isEligableForPromotion(const Employee& employee)
{
	return employee.workExperience >= 10;
}

// 10% raise for those employees eligable for promotion
// update the file
bool raiseWages(const char* inputFileName)
{
	std::ifstream inputFile(inputFileName, std::ios::in);

	if (!inputFile.is_open())
	{
		std::cout << "The input file cannot be used! Error occurred while opening...." << std::endl;
		return false;
	}

	// the records are stored in a temporary file
	std::ofstream outputFile("Temp.txt", std::ios::out);

	if (!outputFile.is_open())
	{
		std::cout << "The output file cannot be used! Error occurred while opening...." << std::endl;
		return false;
	}

	Employee employee{};
	while (inputFile)
	{
		if (readEmployee(inputFile, employee))
		{
			if (isEligableForPromotion(employee))
			{
				employee.wage *= 1.1;
			}

			// wages of those not eligable for promotion will not be updated
			printEmployee(outputFile, employee);
		}
	}

	// close does not clear the state of the input stream
	inputFile.clear();
	inputFile.close();

	outputFile.close();

	bool oldFileSuccessfullyRemoved = (0 == std::remove(inputFileName));
	bool tempFileSuccessullyRenamed = (0 == std::rename("Temp.txt", inputFileName));

	return oldFileSuccessfullyRemoved && tempFileSuccessullyRenamed;
}

int main()
{
	const char* inputFileName = "Employees.txt";

	std::cout << "The content of the file " << inputFileName << " is the following: " << std::endl;
	showFileEmployeesContent(inputFileName);

	filterEmployees(inputFileName, "SelectedForPromotion.txt", isEligableForPromotion);

	raiseWages(inputFileName);

	return 0;
}
