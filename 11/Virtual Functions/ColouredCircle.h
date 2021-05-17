#ifndef COLOUREDCIRCLE_H
#define COLOUREDCIRCLE_H

#include "Circle.h"
#include "Point.h"

#include <string>

class ColouredCircle : public Circle
{
	public:
		ColouredCircle(const Point& center, double radius, const std::string& colour);
		virtual ~ColouredCircle();

		const std::string& getColour() const { return this->colour; }
		void setColour(const std::string& colour);

		virtual void print(std::ostream& out = std::cout) const override;

	private:
		std::string colour;
};

// няма нужда, ще се използва дефинираният за базовия клас, 
// в който е извикана виртуалната функция print

//std::ostream& operator<<(std::ostream& out, const ColouredCircle& circle);

#endif // !COLOUREDCIRCLE_H
