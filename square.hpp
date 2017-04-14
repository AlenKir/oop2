#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "line.hpp"
class Square : public virtual Shape
{
public:
	Square() {}
	Square(const Point& leftTop, const Point& rightBottom)
	{
		_left = new Line(leftTop, Point(leftTop.getX(), rightBottom.getY()));
		_top = new Line(leftTop, Point(rightBottom.getX(), leftTop.getY()));
		_right = new Line(Point(rightBottom.getX(), leftTop.getY()), rightBottom);
		_bottom = new Line(Point(leftTop.getX(), rightBottom.getY()), rightBottom);
	}
	virtual void draw(Screen* screen) const
	{
		std::cout << "square draw" << std::endl;
		_left->draw(screen);
		_top->draw(screen);
		_right->draw(screen);
		_bottom->draw(screen);
	}
	virtual void move(Point p)
	{
		_left->move(p);
		_top->move(p);
		_right->move(p);
		_bottom->move(p);
	}
	Point getLeftTop() const
	{
		return _left->getLeftTop();
	}
	Point getRightTop() const
	{
		return _right->getRightTop();
	}
	Point getLeftBottom() const
	{
		return _left->getLeftBottom();
	}
	Point getRightBottom() const
	{
		return _right->getRightBottom();
	}
	virtual ~Square()
	{
		delete _left;
		delete _top;
		delete _right;
		delete _bottom;
	}
protected:
	Line *_left, *_top, *_right, *_bottom;
};
#endif //SQUARE_HPP