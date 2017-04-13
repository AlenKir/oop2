#include <vector>
#include <memory>
#include "line.hpp"
#include "screen.hpp"
#include "square.hpp"

int main()
{
	auto screen = std::make_unique<Screen>(50, 35);

	std::vector<std::shared_ptr<Shape>> shapes; //вектор фигур

	shapes.emplace_back(std::make_shared<Square>(Point(15, 3), Point(32, 12))); // Шляпа (видимо, поместили назад)

	Point p1 = shapes[shapes.size() - 1]->getLeftBottom(); //запрашиваем левый нижний угол шляпы
														   //устанавливаем координаты точки чуть меньше? 
														   //чтобы потом, когда будем рисовать, поля шляпы не поехали вправо
	p1.setX(p1.getX() - 2);
	p1.setY(p1.getY() + 1);

	Point p2 = shapes[shapes.size() - 1]->getRightBottom(); //запрашиваем правый нижний угол шляпы
															//чтобы поля не поехали влево
	p2.setX(p2.getX() + 2);
	p2.setY(p2.getY() + 1);

	shapes.emplace_back(std::make_shared<Line>(p1, p2)); // Линия под шляпой (ее поля)

	p1 = shapes[shapes.size() - 1]->getLeftBottom(); //запрашиваем левый край линии
													 //смещаемся чуть вправо и вниз, чтобы оставить место для полей
	p1.setX(p1.getX() + 1);
	p1.setY(p1.getY() + 1);

	p2 = shapes[shapes.size() - 1]->getRightBottom(); //запрашиваем правый край линии
													  //смещаемся для нижнего края лица на 10, для правого края на 1 влево
	p2.setX(p2.getX() - 1);
	p2.setY(p2.getY() + 10);

	shapes.emplace_back(std::make_shared<Square>(p1, p2)); // Рисуем голову

	Point eyeLeft = shapes[shapes.size() - 1]->getLeftTop();
	eyeLeft.setX(eyeLeft.getX() + 2);
	eyeLeft.setY(eyeLeft.getY() + 2);
	Point eyeRight = Point(eyeLeft.getX() + 2, eyeLeft.getY());
	shapes.emplace_back(std::make_shared<Line>(eyeLeft, eyeRight)); // Левый глаз
	eyeRight = shapes[shapes.size() - 2]->getRightTop();
	eyeRight.setX(eyeRight.getX() - 2);
	eyeRight.setY(eyeRight.getY() + 2);
	eyeLeft = Point(eyeRight.getX() - 2, eyeRight.getY());
	shapes.emplace_back(std::make_shared<Line>(eyeLeft, eyeRight)); // Правый глаз
	std::shared_ptr<Shape> leftEye = shapes[shapes.size() - 2];
	std::shared_ptr<Shape> rightEye = shapes[shapes.size() - 1];
	Point nose = Point(leftEye->getRightTop().getX() +
		(rightEye->getLeftTop().getX() - leftEye->getRightTop().getX()) / 2,
		leftEye->getRightTop().getY() + 2);
	shapes.emplace_back(std::make_shared<Line>(nose, nose)); // Нос
	std::shared_ptr<Shape> head = shapes[shapes.size() - 4];
	p1 = head->getLeftBottom(); p1.setX(p1.getX() + 2); p1.setY(p1.getY() - 2);
	p2 = head->getRightBottom(); p2.setX(p2.getX() - 2); p2.setY(p2.getY() - 2);
	shapes.emplace_back(std::make_shared<Line>(p1, p2)); // Рот
	auto costume = std::make_shared<Line>(Point(p1.getX(), p1.getY() + 10),
		Point(p2.getX(), p2.getY() + 10));
	shapes.emplace_back(costume); //Линия костюма
	p1 = Point(costume->getLeftBottom().getX(), costume->getLeftBottom().getY() + 1);
	auto leftDot = std::make_shared<Line>(p1, p1);
	shapes.emplace_back(leftDot); //Левая точка
	p1 = Point(costume->getRightBottom().getX(), costume->getRightBottom().getY() + 1);
	auto rightDot = std::make_shared<Line>(p1, p1);
	shapes.emplace_back(rightDot); //Правая точка
	for (auto shape : shapes)
		shape->draw(screen.get());
	screen->draw();
	std::cin.get();
	return 0;
}