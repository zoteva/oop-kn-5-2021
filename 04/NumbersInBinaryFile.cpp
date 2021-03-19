#include <fstream>
#include <iostream>

bool transferNumbersFromTextToBinary(const char* inputFileName, const char* outputFileName)
{
	std::ifstream inputFile(inputFileName, std::ios::in);

	if (!inputFile.is_open())
	{
		std::cout << "Input file cannot be opened!" << std::endl;
		return false;
	}

	std::ofstream outputFile(outputFileName, std::ios::out | std::ios::binary);
	if (!outputFile)
	{
		std::cout << "Output file cannot be opened!" << std::endl;
		return false;
	}
	
	int currentNumber = 0;

	while (inputFile)
	{
		inputFile >> currentNumber;

		if (inputFile)
		{
			std::cout << "current: " << currentNumber << std::endl;
		
			outputFile.write(reinterpret_cast<const char*>(&currentNumber), sizeof(currentNumber));
		}
		else
		{
			if (inputFile.eof())
			{
				std::cout << "End of file reached!" << std::endl;
			}
			else
			{
				inputFile.clear();
				inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
			}
		}
	}
	
	inputFile.close();
	outputFile.close();

	return true;
}

void rewind(std::fstream& file)
{
	file.clear();
	file.seekg(0, std::ios::beg);
}

long long countNumbersStoredInFile(std::fstream& file)
{
	if (!file)
		return 0;

	// set the get pointer at the end of the file
	file.seekg(0, std::ios::end);

	std::streamoff sizeOfFile = file.tellg();

	// check if the size of the file % size of int == 0
	long long countNumbers = sizeOfFile / sizeof(int);

	rewind(file);

	return countNumbers;
}

void changeNumber(std::fstream& file, size_t index, int newValue)
{
	if (!file)
		return;
	
	long long countNumbers = countNumbersStoredInFile(file);

	if (index >= countNumbers)
	{
		std::cout << "Invalid position in the file!" << std::endl;
		return;
	}

	size_t changePosition = index * sizeof(int);

	file.seekp(changePosition, std::ios::beg);
	std::cout << "Put position: " << file.tellp() << std::endl;

	file.write(reinterpret_cast<const char*>(&newValue), sizeof(int));
}

void showBinaryFileContent(std::fstream& file)
{
	if (!file)
		return;

	int currentNumber{ 0 };
	while (file)
	{
		file.read(reinterpret_cast<char*>(&currentNumber), sizeof(int));
		
		if (file.gcount() == sizeof(int))
		{
			std::cout << currentNumber << '\t';
		}
	}

	rewind(file);
}

int main()
{
	//transferNumbersFromTextToBinary("Numbers.txt", "Numbers.bin");

	const char* fileName = "Numbers.bin";

	std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!file)
	{
		std::cout << "File cannot be opened!" << std::endl;
		return -1;
	}

	showBinaryFileContent(file);

	std::cout << "\n--- Modify the 3rd number" << std::endl;
	changeNumber(file, 2, 666);

	rewind(file);
	showBinaryFileContent(file);

	file.close();

	return 0;
}