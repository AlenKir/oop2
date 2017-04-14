#include "square.hpp"
#include "cross.hpp"
#include <cstdint>
#include <cmath>
#include <vector>
#include <memory>
class CrossedSquare : public virtual Square, public virtual Cross
{
public:
	CrossedSquare(const Point& leftTop, const Point& rightBottom/*, const Point& left, const Point& top*/)
	{
		/*Square::Square(leftTop, rightBottom);*/
		_left = new Line(leftTop, Point(leftTop.getX(), rightBottom.getY()));
		_top = new Line(leftTop, Point(rightBottom.getX(), leftTop.getY()));
		_right = new Line(Point(rightBottom.getX(), leftTop.getY()), rightBottom);
		_bottom = new Line(Point(leftTop.getX(), rightBottom.getY()), rightBottom);

		
		Point left = coordCrossLeft(leftTop, rightBottom);
		Point top = coordCrossTop(leftTop, rightBottom);

		Point p1, p2;
		Point p3, p4;
		p1 = left;
		p2 = coordCrossRight(leftTop, rightBottom);
		//p2 = Point(top.getX() + top.getX() - left.getX(), left.getY());
		p3 = top;
		//p4 = Point(top.getX(), left.getY() - top.getY() + left.getY());
		p4 = coordCrossBttm(leftTop, rightBottom);
		_first = new Line(p1, p2);
		_second = new Line(p3, p4);
	}

	Point coordCrossLeft(const Point& leftTop, const Point& rightBottom)
	{
		int distance = rightBottom.getY() - leftTop.getY();
		Point l = Point(leftTop.getX(), leftTop.getY() + distance / 2);
		return l;
	}
	Point coordCrossTop(const Point& leftTop, const Point& rightBottom)
	{
		int distance = rightBottom.getX() - leftTop.getX();
		Point t = Point(leftTop.getX() + distance / 2, leftTop.getY());
		return t;
	}
	Point coordCrossBttm(const Point& leftTop, const Point& rightBottom)
	{
		int distance = rightBottom.getX() - leftTop.getX();
		distance /= 2;
		Point bttm = Point(leftTop.getX() + distance, rightBottom.getY());
		return bttm;
	}
	Point coordCrossRight(const Point& leftTop, const Point& rightBottom)
	{
		int distance = rightBottom.getY() - leftTop.getY();
		distance /= 2;
		Point bttm = Point(rightBottom.getX(), leftTop.getY()+distance);
		return bttm;
	}

	virtual void draw(Screen* screen) const
	{
		std::cout << "crossedsquare draw" << std::endl;
		_left->draw(screen);
		_top->draw(screen);
		_right->draw(screen);
		_bottom->draw(screen);
		
		_first->draw(screen);
		_second->draw(screen);
	}
	virtual void move(Point p)
	{
	
		_left->move(p);
		_top->move(p);
		_right->move(p);
		_bottom->move(p);

		
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