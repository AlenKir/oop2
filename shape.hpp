#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "screen.hpp"
class Shape
{
public:
	virtual void draw(Screen* screen) const = 0;
	virtual void move(Point p) = 0;
	virtual Point getLeftTop() const = 0;
	virtual Point getRightTop() const = 0;
	virtual Point getLeftBottom() const = 0;
	virtual Point getRightBottom() const = 0;
	virtual ~Shape() {}
};
#endif //SHAPE_HPP
