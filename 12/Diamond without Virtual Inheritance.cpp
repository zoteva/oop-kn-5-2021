#include <iostream>

class A
{
    protected:
        int a;

    public:
        A(int newA): a(newA)
        {}

        void print() const
        {
            std::cout << "&a = " << &a << std::endl;
            std::cout << "A::a = " << a << std::endl;
        }

        void otherFunction() const
        {
            std::cout << "A::otherFunction has been called!\n";
        }

        ~A()
        {
            std::cout << "~A" << std::endl;
        }
};

class B: public A
{
    protected:
        int b;

		void printOwn() const
		{
            std::cout << "&b = " << &b << std::endl;
            std::cout << "B::b = " << b << std::endl;
		}

    public:
        B(int newA, int newB): A(newA), b(newB)
        {}

        void print() const
        {
            std::cout << "--- B::print() ---" << std::endl;
            A::print();
			printOwn();
            std::cout << "------------------" << std::endl;
        }

        ~B()
        {
            std::cout << "~B" << std::endl;
        }
};

class C: public A
{
    protected:
        int c;

		void printOwn() const
		{
            std::cout << "&c = " << &c << std::endl;
            std::cout << "C::c = " << c << std::endl;
		}

    public:
        C(int newA, int newC): A(newA), c(newC)
        {}

        void print() const
        {
            std::cout << "--- C::print() ---" << std::endl;
            A::print();
			printOwn();
            std::cout << "------------------" << std::endl;
        }

        ~C()
        {
            std::cout << "~C" << std::endl;
        }
};

class D: public B, public C
{
    private:
        // няма собствени член-данни

    public:
        // обръщение към констукторите на базовите класове
        D(int newAB, int newB, int newAC, int newC): B(newAB, newB), C(newAC, newC)
        {
            // празно тяло, няма собствени член-данни,
            // трябва единствено да извика базовите конструктори
        }

        void print() const
        {
            std::cout << "--- D::print() ---" << std::endl;

            B::print();
            C::print();

            std::cout << "------------------" << std::endl;
        }

        ~D()
        {
            std::cout << "~D" << std::endl;
        }
};

int main()
{
    //B b(1, 2);
    //b.otherFunction();

    D d(1, 2, 2, 3);

    d.print();
    //d.otherFunc();

    //std::cout << "Inherited member A::print (A-B-D): ";
    //// как да извикаме print по тази линия на наследяване?
    //static_cast<const A*>(static_cast<const B*>(&d))->otherFunction();
    //
    //std::cout << "Inherited member A::print (A-C-D): ";
    //// как да извикаме print по тази линия на наследяване?
    //static_cast<const A*>(static_cast<const C*>(&d))->otherFunction();

    // преобразуване до указатели към базовите класове
    //std::cout << "Calling the print function..." << std::endl;
    //B* ptrB = &d;
    //ptrB->print();

    //C* ptrC = &d;
    //ptrC->print();

    // преобразуването до указател от базовия клас A
    // не е възможно, по кой път да се тръгне?
    //A* ptrA = &d;
    //ptrA->print();
}
