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

// shows an employee data on the standard output
void showInfo(const Employee& employee)
{
	std::cout << std::setw(5) << employee.id
		<< std::setw(20) << employee.name
		<< std::setw(20) << employee.position
		<< std::setw(10) << employee.workExperience
		<< std::setw(10) << std::setiosflags(std::ios::fixed) << std::setprecision(2) << employee.wage << std::endl;
}

// reads an employee from a text file,
// tab is used as a separator
bool readFromTextFile(std::ifstream& inputFile, Employee& employee)
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

// USE Binary Files

// read an employee from a binary file
bool readFromBinary(std::fstream& inputFile, Employee& employee)
{
	// the file cannot be read 
	if (!inputFile) return false;

	inputFile.read(reinterpret_cast<char*>(&employee), sizeof(employee));

	return inputFile.good() && inputFile.gcount() == sizeof(employee);
}

// save an employee in a binary file
bool writeToBinary(std::fstream& outputFile, const Employee& employee)
{
	if (!outputFile) return false;

	outputFile.write(reinterpret_cast<const char*>(&employee), sizeof(employee));
	return outputFile.good();
}

void createABinaryFile(const char* inputFileName, const char* outputFileName)
{
	std::ifstream inputFile(inputFileName, std::ios::in);

	if (!inputFile.is_open())
	{
		std::cout << "The input file cannot be used! Error occurred while opening...." << std::endl;
		return;
	}

	std::fstream outputFile(outputFileName, std::ios::out | std::ios::binary);
	if (!outputFile.is_open())
	{
		std::cout << "The output file cannot be used! Error occurred while opening...." << std::endl;
		return;
	}

	Employee employee{};
	while (inputFile)
	{
		if (readFromTextFile(inputFile, employee))
		{
			writeToBinary(outputFile, employee);
		}
	}

	inputFile.close();
	outputFile.close();
}

void rewind(std::fstream& file)
{
	file.clear();
	file.seekg(0, std::ios::beg);
}

long long findNumberOfEmployeesInBinaryFile(std::fstream& file)
{
	if (!file)
		return 0;

	// set the get pointer at the end of the file
	file.seekg(0, std::ios::end);

	std::streamoff sizeOfFile = file.tellg();
	long long numberOfEmployees = sizeOfFile / sizeof(Employee);

	rewind(file);

	return numberOfEmployees;
}

// read from a binary file
void showFileEmployeesContent(const char* inputFileName)
{
	std::fstream inputFile(inputFileName, std::ios::in | std::ios::binary);

	if (!inputFile.is_open())
	{
		std::cout << "The input file cannot be used! Error occurred while opening...." << std::endl;
		return;
	}

	std::cout << "Expected " << findNumberOfEmployeesInBinaryFile(inputFile) << " employees." << std::endl;

	Employee employee{};
	while (inputFile)
	{
		if (readFromBinary(inputFile, employee))
		{
			showInfo(employee);
		}
	}

	inputFile.close();
}

using Predicate = bool (*) (const Employee&);

bool isEligableForPromotion(const Employee& employee)
{
	return employee.workExperience >= 10;
}

// 10% raise for those employees eligable for promotion
// update the file, the file should be opened for reading and writing
void raiseWages(const char* fileName)
{
	std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "The file cannot be used for reading! Error occurred while opening...." << std::endl;
		return;
	}

	std::cout << "-- (Initial) get position: " << file.tellg() << "\t put position: " << file.tellp() << std::endl;

	Employee employee{};
	while (file)
	{
		// the position before reading
		std::streampos start = file.tellg();

		if (readFromBinary(file, employee))
		{
			// position after the read operation
			std::streampos end = file.tellg();
			std::cout << "-- (Reading) get position: " << file.tellg() << "\t put position: " << file.tellp() << std::endl;

			if (isEligableForPromotion(employee))
			{
				employee.wage *= 1.1;

				// put and get positions move together, 
				// be sure to set the two positions at the right places when you need to perform 
				// the respective operation

				// get back to the start of the employee
				file.seekp(start, std::ios::beg);
				std::cout << "-- (Seekp) get position: " << file.tellg() << "\t put position: " << file.tellp() << std::endl;

				writeToBinary(file, employee);
				std::cout << "-- (Writing) get position: " << file.tellg() << "\t put position: " << file.tellp() << std::endl;

				// restore the get position where the next reading operation should be performed
				file.seekg(end, std::ios::beg);
			}
		}
	}

	// close does not clear the state of the input stream
	file.close();
}

int main()
{
	//createABinaryFile("Employees.txt", "Employees.bin");

	const char* fileName = "Employees.bin";

	std::cout << "The content of the file " << fileName << " is the following: " << std::endl;
	showFileEmployeesContent(fileName);

	raiseWages(fileName);

	std::cout << "--- There has been a raise for some of the employees --- \n";
	showFileEmployeesContent(fileName);

	return 0;
}
