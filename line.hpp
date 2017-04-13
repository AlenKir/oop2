#ifndef LINE_HPP
#define LINE_HPP
#include "shape.hpp"
#include "screen.hpp"
#include <algorithm>
class Line : public Shape
{
public:
	Line(const Point& a, const Point& b)
	{
		_a = a;
		_b = b;
	}
	Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
	{
		_a = Point(x0, y0);
		_b = Point(x1, y1);
	}
	Line(const Line& source)
	{
		_a = source._a;
		_b = source._b;
	}
	void draw(Screen* screen) const
	{
		screen->putLine(_a.getY(), _a.getX(), _b.getY(), _b.getX());
	}
	void move(Point p)
	{
		_a.setX(_a.getX() + p.getX()); _a.setY(_a.getY() + p.getY());
		_b.setX(_b.getX() + p.getX()); _b.setY(_b.getY() + p.getY());
	}
	Point getLeftTop() const
	{
		return Point(std::min(_a.getX(), _b.getX()), std::min(_a.getY(), _b.getY()));
	}
	Point getRightTop() const
	{
		return Point(std::max(_a.getX(), _b.getX()), std::min(_a.getY(), _b.getY()));
	}
	Point getLeftBottom() const
	{
		return Point(std::min(_a.getX(), _b.getX()), std::max(_a.getY(), _b.getY()));
	}
	Point getRightBottom() const
	{
		return Point(std::max(_a.getX(), _b.getX()), std::max(_a.getY(), _b.getY()));
	}
	Point getFirstPoint() const
	{
		return _a;
	}
	Point getSecondPoint() const
	{
		return _b;
	}
protected:
	Point _a;
	Point _b;
};
#endif // LINE_HPP