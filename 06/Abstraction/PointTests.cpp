// #include "Point.h"

// change only the header file to include the other definition of point
// no need to change anything here (abstraction level: application)
#include "PointPolarCoordinates.h"

#include <iostream>

void read(Point& p)
{
	int x = 0;
	std::cout << "x = ";
	std::cin >> x;

	int y = 0;
	std::cout << "y = ";
	std::cin >> y;

	p.changeCoordinates(x, y);
}

void readArray(Point* points, unsigned n)
{
	for (unsigned i = 0; i < n; ++i)
	{
		read(points[i]);
	}
}

void printArray(const Point* arr, unsigned n)
{
	for (unsigned i = 0; i < n; ++i)
	{
		arr[i].print();
	}
}

Point findClosestToCenter(const Point* points, unsigned n)
{
	double minDistance = points[0].distanceToCenter();
	unsigned minIndex = 0;

	for (unsigned i = 1; i < n; ++i)
	{
		double currentDistance = points[i].distanceToCenter();

		if (currentDistance < minDistance)
		{
			minDistance = currentDistance;
			minIndex = i;
		}
	}

	return points[minIndex];
}


int main()
{
	Point center{};
	std::cout << "Center: "; center.print();

	Point points[20];

	size_t numberOfPoints = 0;
	std::cout << "Number of points: ";
	std::cin >> numberOfPoints;

	readArray(points, numberOfPoints);
	printArray(points, numberOfPoints);

	std::cout << "The point closest to the center is: ";
	Point closestToCenter = findClosestToCenter(points, numberOfPoints);
	closestToCenter.print();

	return 0;
}