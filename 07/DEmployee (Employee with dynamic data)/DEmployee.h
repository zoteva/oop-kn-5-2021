#ifndef DEMPLOYEE_H_INCLUDED
#define DEMPLOYEE_H_INCLUDED

class DEmployee
{
	public:
		DEmployee(const char* newName, const char* newPosition, double salary);
		DEmployee(const DEmployee& other);
		DEmployee& operator=(const DEmployee& other);

		// move constructor
		DEmployee(DEmployee&& other) noexcept;

		// move assignment operator
		DEmployee& operator=(DEmployee&& other) noexcept;

		~DEmployee();

		const char* getName() const;
		const char* getPosition() const;
		double getSalary() const;

		void setName(const char* newName);
		void setPosition(const char* newPosition);
		void setSalary(double newSalary);

		void print() const;

	private:
		char* name;
		char* position;
		double salary;

		// used in the copy assignement operator
		void swap(DEmployee& other);
};

#endif // !DEMPLOYEE_H_INCLUDED
