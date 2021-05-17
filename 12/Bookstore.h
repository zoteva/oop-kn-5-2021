#ifndef BOOKSTORE_H_INCLUDED
#define BOOKSTORE_H_INCLUDED

#include "PrintEdition.h"

#include <string>
#include <vector>

class Bookstore
{
	public:
		Bookstore(const char* _name);
		Bookstore(const Bookstore& other);
		Bookstore& operator=(const Bookstore& other);
		~Bookstore();

		const char* getName() const;
		void setName(const char* _name);

		Bookstore& addPrintEdition(const PrintEdition& newPE);

		size_t countPrintEditions() const;

		PrintEdition& getPrintEditionAt(size_t position);
		const PrintEdition& getPrintEditionAt(size_t position) const;
		
		void print() const;

	private:
		void copyCollection(const std::vector<PrintEdition*>& otherCollection);
		void eraseCollection();

	private:
		std::vector<PrintEdition*> mCollection;
		char* mName;
};

#endif // !BOOKSTORE_H_INCLUDED



