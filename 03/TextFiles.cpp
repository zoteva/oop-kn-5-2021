#include <iostream>
#include <fstream>
#include <limits>

int main()
{
	// input file stream connected to the file
	std::ifstream in("Numbers.txt", std::ios::in);

	// check if the file has been opened successfully for reading
	if (!in.is_open())
	{
		std::cout << "File cannot be opened!" << std::endl;
		return -1;
	}

	int sum = 0;
	int currentNumber = 0;

	// while the state of the stream is good...
	while (in)
	{
		in >> currentNumber;

		// check if the last operation performed is successful
		if (in)
		{
			std::cout << "current: " << currentNumber << std::endl;
			sum += currentNumber;
		}
		else
		{
			if (in.eof())
			{
				std::cout << "End of file reached!" << std::endl;
			}
			else
			{
				// the state of the input stream is fail
				std::cout << "Last operation has failed!" << std::endl;

				// clears the state of the stream, 
				// the stream is back to good state, nothing more...
				in.clear();

				// we have to remove the erroneous data from the stream
				in.ignore(std::numeric_limits<std::streamsize>::max(), '\t');

				// OR
				// while(in.get() != '\t');
			}
		}
	}

	std::cout << "Sum: " << sum << std::endl;

	in.close();
}