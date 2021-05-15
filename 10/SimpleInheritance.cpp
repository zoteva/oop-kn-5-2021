#include <iomanip>
#include <iostream>

class BaseObject
{
	public:
        BaseObject(int initialID = 0) 
            : id(initialID)
        {
            std::cout << "Create ( BaseObject )" << std::endl;
            print();
        }

        ~BaseObject()
        {
            std::cout << "~Create( BaseObject )" << std::endl;
            print();
        }

        int getID() const { return this->id; }

        void setID(int newID) { this->id = newID; }

        void print() const
        {
            std::cout << "ObjectID: " << id << std::endl;
        }

	private:
		int id;
};

class DerivedObject: public BaseObject
{
    public:
        DerivedObject(int initialID, double initialCost)
            : BaseObject(initialID), cost(initialCost)
        {
            std::cout << "Create( DerivedObject )" << std::endl;
            print();
        }

        ~DerivedObject()
        {
            std::cout << "~Create( DerivedObject )" << std::endl;
            print();
        }

        double getCost() const { return this->cost; }
        void setCost(double newCost) { this->cost = newCost; }

        void print() const
        {
            // производният клас няма директен достъп до член-данните на базовия клас
            // те са разположени в private частта
            //std::cout << "Object ID: " << this->id << std::endl;

            // можем да използваме или селекторът getID()
            // а най-добре, да преизползваме функцията print() на базовия клас
            BaseObject::print();

            std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
            std::cout << "Cost: " << cost << std::endl;
        }

    private:
        double cost;
};

void doSmthWithObject(const BaseObject& o)
{
    std::cout << "\nDo something with an object with ID..." << std::endl;
    o.print();
}

void doSmthWithObjectWithCost(const DerivedObject& o)
{
    std::cout << "\nDo something with an object with cost..." << std::endl;
    o.print();
}

int main()
{
    BaseObject o(1);
    o.print();
    doSmthWithObject(o);
    // преобразуването от базов към производен е невъзможно!
    //doSmthWithObjectWithCost(o);

    std::cout << "----------------" << std::endl;
    DerivedObject dero(2, 2.50);
    dero.print();
    doSmthWithObject(dero);
    doSmthWithObjectWithCost(dero);
    std::cout << "----------------" << std::endl;

    // копиране на обектите
    // преобразуването от базов към производен е невъзможно!
    //oc = o;

    std::cout << "Assign to the base object" << std::endl;
    o = dero;
    o.print();
    
    return 0;
}
