#include "Bookstore.h"
#include "Magazine.h"
#include "Comics.h"

#include <iostream>
#include <stdexcept>

typedef bool (*Predicate)(const PrintEdition&);

void showPrintEditionByName(const Bookstore& bookstore, const char* name)
{
	size_t countPrintEditions = bookstore.countPrintEditions();
	for (size_t i = 0; i < countPrintEditions; ++i)
	{
		const PrintEdition& currentEdition = bookstore.getPrintEditionAt(i);
		if (strcmp(currentEdition.getName(), name) == 0)
		{
			currentEdition.print();
		}
	}
}

size_t countWeeklyComics(const Bookstore& bookstore)
{
	size_t count = 0;

	size_t countPrintEditions = bookstore.countPrintEditions();
	for (size_t i = 0; i < countPrintEditions; ++i)
	{
		const PrintEdition& currentEdition = bookstore.getPrintEditionAt(i);

		try
		{
			const Comics& comics = dynamic_cast<const Comics&>(currentEdition);
			if (comics.getPeriodicity() == Magazine::Periodicity::WEEKLY)
			{
				++count;
			}
		}
		catch (const std::bad_cast& ex)
		{
			// нищо...
			// просто елементът на тази позиция не е комикс
		}
	}

	return count;
}

size_t countPrintEditionsThatMeetCondition(const Bookstore& bookstore, Predicate pred)
{
	size_t count = 0;

	size_t countPrintEditions = bookstore.countPrintEditions();
	for (size_t i = 0; i < countPrintEditions; ++i)
	{
		const PrintEdition& currentEdition = bookstore.getPrintEditionAt(i);
		if (pred(currentEdition))
		{
			++count;
		}
	}

	return count;
}

bool isBook(const PrintEdition& pe)
{
	const Book* pBook = dynamic_cast<const Book*>(&pe);
	const Comics* pComics = dynamic_cast<const Comics*>(&pe);

	// книга е, но не е комикс
	return pBook != nullptr && pComics == nullptr;
}

int main()
{
	// обект от клас PrintEdition не може да бъде създаден
	// класът е обастрактен
	//PrintEdition oldPE(1900, "Old Print Edition", 1000);

	// невалидна периодичност => очакваме изключение от конструктора на класа Magazine
	//try
	//{
	//	Magazine nationalGeographic("National Geographic", 2.50, 2021, static_cast<Magazine::Periodicity>(7));
	//}
	//catch (const std::invalid_argument& ex)
	//{
	//	std::cout << "Exception has been caught: " << ex.what() << std::endl;
	//}

	//Book kaloiansDaughter(2015, "The daughter of Kaloian", 12.00, "Fani Popova-Mutafova");
	//kaloiansDaughter.print();

	//PrintEdition* naruto = new Comics(2003, "Naruto", 13.50, "Masashi Kishimoto", Magazine::Periodicity::MONTHLY);
	//naruto->print();

	//delete naruto;

	Bookstore bookstore("My bookstore");
	bookstore
		.addPrintEdition(Magazine("National Geographic", 2.50, 2021, Magazine::Periodicity::MONTHLY))
		.addPrintEdition(Book(2015, "The daughter of Kaloian", 12.00, "Fani Popova-Mutafova"))
		.addPrintEdition(Book(1950, "1984", 10.90, "George Orwell"))
		.addPrintEdition(Magazine("National Geographic", 2.50, 2021, Magazine::Periodicity::MONTHLY))
		.addPrintEdition(Comics(2003, "Naruto", 13.50, "Masashi Kishimoto", Magazine::Periodicity::MONTHLY))
		.addPrintEdition(Comics(2000, "Death Note", 0.0, "O", Magazine::Periodicity::WEEKLY));

	//bookstore.print();
	//showPrintEditionByName(bookstore, "Naruto");

	//std::cout << "Count weekly comics: " << countWeeklyComics(bookstore) << std::endl;
	
	std::cout << "Count books: " << countPrintEditionsThatMeetCondition(bookstore, isBook) << std::endl;

	return 0;
}