#include "Point.h"

#include <cmath>
#include <iomanip>
#include <iostream>

Point::Point(double x, double y) 
    : x(x), y(y)
{}

double Point::getX() const
{
    return this->x;
}

double Point::getY() const
{
    return this->y;
}

double Point::getR() const
{
    return std::sqrt(this->x * this->x + this->y * this->y);
}

double Point::getTheta() const
{
    // valid only for a point in x > 0 && y > 0
    return std::atan2(this->y, this->x);
}

double Point::distanceToCenter() const
{
    return this->getR();
}

double Point::distanceTo(const Point& other) const
{
    double distance = 
        std::sqrt((this->getX() - other.getX()) * (this->getX() - other.getX()) + 
                  (this->getY() - other.getY()) * (this->getY() - other.getY()));
    return distance;
}

void Point::changeCoordinates(double x, double y)
{
    this->x = x;
    this->y = y;
}

void Point::print() const
{
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) 
        << "(" << this->getX() << ", " << this->getY() << ")" << std::endl;
}