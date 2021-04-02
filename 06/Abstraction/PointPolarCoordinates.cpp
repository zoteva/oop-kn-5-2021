#include "PointPolarCoordinates.h"

#include <cmath>
#include <iomanip>
#include <iostream>

Point::Point(double x, double y) 
{
    this->changeCoordinates(x, y);
}

double Point::getX() const
{
    return this->r * std::cos(this->theta);
}

double Point::getY() const
{
    return this->r * std::sin(this->theta);
}

double Point::getR() const
{
    return this->r;
}

double Point::getTheta() const
{
    return this->theta;
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
    this->r = std::sqrt(x * x + y * y);
    // x > 0, y > 0
    this->theta = atan(y / x);
}

void Point::print() const
{
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) 
        << "(" << this->getX() << ", " << this->getY() << ")" << std::endl;
}