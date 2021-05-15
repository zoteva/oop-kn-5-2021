#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

class Circle
{
    public:
        Circle(double x = 0, double y = 0, double r = 0);
        Circle(const Point&, double);
        ~Circle();
    
        const Point& getCenter() const
        {
            return center;
        }

        double getRadius() const
        {
            return radius;
        }

        void print() const;

        void setRadius(double);
        void setCenter(double, double);
        void setCenter(const Point&);

        // проверява дали дадена точка е вътрешна за окръжността
        bool isInside(const Point& ) const;
        // проверява дали двете окръжности се пресичат
        bool intersect(const Circle& ) const;

        friend std::istream& operator >> (std::istream&, Circle&);
        friend std::ostream& operator << (std::ostream&, const Circle&);

    private:
        Point center;
        double radius;
};

#endif // CIRCLE_H
