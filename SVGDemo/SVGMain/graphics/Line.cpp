#include "../graphics/Line.h"
#include <cmath>
using namespace std;

Line::Line(const Vector2Df& point1, const Vector2Df& point2, ColorShape stroke, float stroke_width): 
	SVGElement(ColorShape::Transparent, stroke, stroke_width, point1), direction(point2) {}

string Line::getClass() const {
	return "Line";
}

void Line::setDirection(const Vector2Df& direction) {
	this->direction = direction;
}

Vector2Df Line::getDirection() const {
	return direction;
}

float Line::getLength() const {
	return sqrt(direction.x * direction.x + direction.y * direction.y);
}
void Line::printData() const {
	cout << "Line: " << endl;
	cout << "  Point 1: (" << SVGElement::getPosition().x << ", " << SVGElement::getPosition().y << ")" << endl;
	cout << "  Point 2: (" << direction.x << ", " << direction.y << ")" << endl;
	cout << "  Direction: (" << direction.x - SVGElement::getPosition().x << ", " << direction.y - SVGElement::getPosition().y << ")" << endl;
	cout << "  Length: " << getLength() << endl;
	cout << "  Fill Color: " << SVGElement::getFillColor() << endl;
	cout << "  Outline Color: " << SVGElement::getOutlineColor() << endl;
	cout << "  Outline Thickness: " << SVGElement::getOutlineThickness() << endl;

}
vector<string> Line::getTransforms() const {
	return SVGElement::getTransforms();
}
SVGElement* Line::getParent() const {
	return SVGElement::getParent();
}
void Line::addElement(SVGElement* element) {
	SVGElement::addElement(element);
}
Vector2Df Line::getMinBound() const {
	return SVGElement::getPosition();
}
Vector2Df Line::getMaxBound() const {
	return Vector2Df(direction.x, direction.y);
}

