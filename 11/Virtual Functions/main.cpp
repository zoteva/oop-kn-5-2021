#include "Circle.h"

#include <fstream>
#include <iostream>

#include "ColouredCircle.h"

size_t countBlueCircle(Circle* scatch[], size_t count)
{
    size_t countBlue = 0;

    for (size_t i = 0; i < count; ++ i)
    {
        std::cout << "Current circle: \n";
        scatch[i]->print();

        // ако указателят scatch[i] не е свързан с обект от клас ColouredCircle,
        // pcc ще има стойност nullptr
        ColouredCircle* pcc = dynamic_cast<ColouredCircle*>(scatch[i]);
        if (pcc)
        {
            if (pcc->getColour() == "blue")
                ++countBlue;
        }
    }

    return countBlue;
}

int main()
{
    {
        Circle* blueCircle1 = new ColouredCircle{ {1, 1}, 2, "blue" };
        Circle* blueCircle2 = new ColouredCircle{ {1, 2}, 2, "blue" };
        Circle* redCircle = new ColouredCircle{ {0, 0}, 2, "red" };

        Circle* circle1 = new Circle{ {0, 0}, 2 };
        Circle* circle2 = new Circle{ {2, 2}, 2};

        // масив от указатели към базов клас, за да опишем 
        // хетерогенен (полиморфен) контейнер с окръжности (обикновени и с цвят)

        Circle* scatch[] = { blueCircle1, blueCircle2, redCircle, circle1, circle2 };

        std::cout << "\n-------------------------------------\n";
        size_t countBlue = countBlueCircle(scatch, 5);

        for (size_t i = 0; i < 5; ++i)
        {
            // тук ще заработят виртуалните деструктори...
            delete scatch[i];
        }

        std::cout << "\n-------------------------------------\n";
    }

    return 0;
}
