#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

#include <iostream>

class Circle
{
    public:
        Circle(double x = 0, double y = 0, double r = 0);
        Circle(const Point& center, double r);
        
        // внимание!
        virtual ~Circle();

        const Point& getCenter() const { return center; }

        double getRadius() const { return radius; }

        // ще бъде предефинирана в производните класове
        virtual void print(std::ostream& out = std::cout) const;

        void setRadius(double);
        void setCenter(double, double);
        void setCenter(const Point&);

        // остават само тук, в производния клас няма да се предефинират
        bool isInside(const Point& ) const;
        bool intersect(const Circle& ) const;

    private:
        Point center;
        double radius;
};

std::ostream& operator<<(std::ostream& out, const Circle& circle);

#endif // CIRCLE_H
