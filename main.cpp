#include <vector>
#include <memory>
#include "line.hpp"
#include "screen.hpp"
#include "square.hpp"
#include "cross.hpp"
#include "crossedsquare.hpp"

int main()
{
	auto screen = std::make_unique<Screen>(50, 35);

	std::vector<std::shared_ptr<Shape>> shapes; //������ �����

	//std::shared_ptr<CrossedSquare> cs(new CrossedSquare(Point(15, 3), Point(32, 13), Point(20, 6), Point(23, 3)));
	shapes.emplace_back(std::make_shared<Cross>(Point(20, 6), Point(23, 3)));
	shapes.emplace_back(std::make_shared<Square>(Point(15, 3), Point(32, 12))); // ����� (������, ��������� �����)

	Point p1 = shapes[shapes.size() - 1]->getLeftBottom(); //����������� ����� ������ ���� �����
														   //������������� ���������� ����� ���� ������? 
														   //����� �����, ����� ����� ��������, ���� ����� �� ������� ������
	p1.setX(p1.getX() - 2);
	p1.setY(p1.getY() + 1);

	Point p2 = shapes[shapes.size() - 1]->getRightBottom(); //����������� ������ ������ ���� �����
															//����� ���� �� ������� �����
	p2.setX(p2.getX() + 2);
	p2.setY(p2.getY() + 1);

	shapes.emplace_back(std::make_shared<Line>(p1, p2)); // ����� ��� ������ (�� ����)

	p1 = shapes[shapes.size() - 1]->getLeftBottom(); //����������� ����� ���� �����
													 //��������� ���� ������ � ����, ����� �������� ����� ��� �����
	p1.setX(p1.getX() + 1);
	p1.setY(p1.getY() + 1);

	p2 = shapes[shapes.size() - 1]->getRightBottom(); //����������� ������ ���� �����
													  //��������� ��� ������� ���� ���� �� 10, ��� ������� ���� �� 1 �����
	p2.setX(p2.getX() - 1);
	p2.setY(p2.getY() + 10);

	shapes.emplace_back(std::make_shared<Square>(p1, p2)); // ������

	Point eyeLeft = shapes[shapes.size() - 1]->getLeftTop(); //����������� ����� ������� ���� ������
	
	Point leftEarLeftTop = eyeLeft;
	leftEarLeftTop.setX(eyeLeft.getX() - 6);
	leftEarLeftTop.setY(eyeLeft.getY() + 2);
	Point leftEarRightBottom = eyeLeft;
	leftEarRightBottom.setX(eyeLeft.getX());
	leftEarRightBottom.setY(eyeLeft.getY() + 6);

	//��� ������ ���� ������ �����
	//��������� �� ��� ������ � ����
	eyeLeft.setX(eyeLeft.getX() + 2);
	eyeLeft.setY(eyeLeft.getY() + 2);
	Point eyeRight = Point(eyeLeft.getX() + 2, eyeLeft.getY()); //������ ���� ������ �����

	shapes.emplace_back(std::make_shared<Line>(eyeLeft, eyeRight)); // ����� ����

	eyeRight = shapes[shapes.size() - 2]->getRightTop(); //����� �� ������ ������ ����

	Point rightEarLeftTop = eyeRight;
	//rightEarLeftTop.setX(eyeRight.getX() + 6);
	rightEarLeftTop.setY(eyeRight.getY() + 2);
	Point rightEarRightBottom = eyeRight;
	rightEarRightBottom.setX(eyeRight.getX() + 6);
	rightEarRightBottom.setY(eyeRight.getY() + 6);

	eyeRight.setX(eyeRight.getX() - 2); //������ ���� ������� ����� �� ��������� ������� ���� ������
	eyeRight.setY(eyeRight.getY() + 2); 
	eyeLeft = Point(eyeRight.getX() - 2, eyeRight.getY()); //����� ���� ������� ����� ������� �� ��� ����� �� ������� ����

	shapes.emplace_back(std::make_shared<Line>(eyeLeft, eyeRight)); // ������ ����

	std::shared_ptr<Shape> leftEye = shapes[shapes.size() - 2];
	std::shared_ptr<Shape> rightEye = shapes[shapes.size() - 1];

	//��� ��������� ���:
	//����� ��������� ��� ��������
	//leftTop, rightBottom : leftEarLeftSide, leftEarRightBottom
	//leftEarLeftTop - �� ������ �����
	//leftEarRightBottom - ���� ������, ���� �� leftEarLeftTop 
	//��������� ��� ������
	//����� ����� �����, ���� ������

	Point nose = Point(leftEye->getRightTop().getX() +
		(rightEye->getLeftTop().getX() - leftEye->getRightTop().getX()) / 2,
		leftEye->getRightTop().getY() + 2);

	shapes.emplace_back(std::make_shared<Line>(nose, nose)); // ���

	std::shared_ptr<Shape> head = shapes[shapes.size() - 4];

	p1 = head->getLeftBottom(); p1.setX(p1.getX() + 2); p1.setY(p1.getY() - 2);
	p2 = head->getRightBottom(); p2.setX(p2.getX() - 2); p2.setY(p2.getY() - 2);

	shapes.emplace_back(std::make_shared<Line>(p1, p2)); // ���

	auto costume = std::make_shared<Line>(Point(p1.getX(), p1.getY() + 10),

		Point(p2.getX(), p2.getY() + 10));

	shapes.emplace_back(costume); //����� �������

	p1 = Point(costume->getLeftBottom().getX(), costume->getLeftBottom().getY() + 1);

	auto leftDot = std::make_shared<Line>(p1, p1);

	//��������� ���

	//shapes.emplace_back(std::make_shared<Square>(leftEarLeftTop, leftEarRightBottom));
	//shapes.emplace_back(std::make_shared<Square>(rightEarLeftTop, rightEarRightBottom));

	shapes.emplace_back(std::make_shared<CrossedSquare>(leftEarLeftTop, leftEarRightBottom));
	shapes.emplace_back(std::make_shared<CrossedSquare>(rightEarLeftTop, rightEarRightBottom));

	shapes.emplace_back(leftDot); //����� �����

	p1 = Point(costume->getRightBottom().getX(), costume->getRightBottom().getY() + 1);

	auto rightDot = std::make_shared<Line>(p1, p1);

	shapes.emplace_back(rightDot); //������ �����

	for (auto shape : shapes)
		shape->draw(screen.get());

	screen->draw();

	std::cin.get();
	return 0;
}