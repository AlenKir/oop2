#include "square.hpp"
#include "cross.hpp"

class CrossedSquare : public virtual Shape, public virtual Cross
{

	CrossedSquare(const Point& leftTop, const Point& rightBottom, const Point& left, const Point& top)
	{
		_left = new Line(leftTop, Point(leftTop.getX(), rightBottom.getY()));
		_top = new Line(leftTop, Point(rightBottom.getX(), leftTop.getY()));
		_right = new Line(Point(rightBottom.getX(), leftTop.getY()), rightBottom);
		_bottom = new Line(Point(leftTop.getX(), rightBottom.getY()), rightBottom);

		Point p1, p2;
		Point p3, p4;
		p1 = left;
		p2 = Point(top.getX() + top.getX() - left.getX(), left.getY());
		p3 = top;
		p4 = Point(top.getX(), left.getY() - top.getY() + left.getY());
		_first = new Line(p1, p2);
		_second = new Line(p3, p4);
	}

	virtual void draw(Screen* screen) const
	{
		//Square::draw(screen);
		_left->draw(screen);
		_top->draw(screen);
		_right->draw(screen);
		_bottom->draw(screen);

		//Cross::draw(screen);
		_first->draw(screen);
		_second->draw(screen);
	}
	virtual void move(Point p)
	{
		//Square::move(p);
		_left->move(p);
		_top->move(p);
		_right->move(p);
		_bottom->move(p);

		//Cross::move(p);
		_first->move(p);
		_second->move(p);
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
	virtual ~CrossedSquare()
	{
		delete _left;
		delete _top;
		delete _right;
		delete _bottom;
		delete _first;
		delete _second;
	}
protected:
	Line *_left, *_top, *_right, *_bottom;
	Line* _first;
	Line* _second;
};