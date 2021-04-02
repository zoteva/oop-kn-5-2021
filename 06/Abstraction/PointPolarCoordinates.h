#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class Point
{
    public:
        Point() = default;
        Point(double x, double y);

        double getX() const;
        double getY() const;

        // how to convert the Cartesian coordinates into radial and angular coordinates?

        // radial distance
        double getR() const;

        // the angle
        double getTheta() const;

        // distance to the center of the coordinate system
        double distanceToCenter() const;
        double distanceTo(const Point& other) const;

        // functions used to modify the values of the data members
        void changeCoordinates(double x, double y);

        void print() const;
    private:
        double r{};
        double theta{};
};

#endif // POINT_H_INCLUDED