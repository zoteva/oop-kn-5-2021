#define _CRT_SECURE_NO_WARNINGS

#include "ColouredCircle.h"

#include <cstring>

// всеки клас се грижи за собствените си член-данни
ColouredCircle::ColouredCircle(const Point& center, double r, const std::string& initialColour)
    : Circle(center, r), colour(initialColour)
{
    std::cout << "\nColouredCircle created" << std::endl;
    print();
}

ColouredCircle::~ColouredCircle()
{
    std::cout << "\n~ColouredCircle() " << std::endl;
    print();
}

void ColouredCircle::print(std::ostream& out) const
{
    Circle::print(out);
    std::cout << "Colour " << this->colour << std::endl;
}

void ColouredCircle::setColour(const std::string& newColour)
{
    this->colour = newColour;
}

//std::ostream& operator<<(std::ostream& out, const ColouredCircle& circle)
//{
//    out << (Circle)circle;
//    out << circle.getColour() << std::endl;
//
//    return out;
//}

