#include "Circle.h"

Circle::Circle(float radius, const Vector2Df& center, ColorShape fill, ColorShape stroke, float stroke_width): MyEllipse(Vector2Df(radius, radius), center, fill, stroke, stroke_width) {}

std::string Circle::getClass() const { 
	return "Circle"; 
}
//vector<string> Circle::getTransforms() const {
//	return this->transforms;
//}
//
//SVGElement* Circle::getParent() const {
//	return parent;
//}
//void Circle::addElement(SVGElement* element) {
//	if (element) {
//		element->setParent(this);
//	}
//}
//void Circle::printData() const {
//	std::cout << "Circle: " << std::endl;
//	std::cout << "Radius: " << getRadius().x << std::endl;
//	std::cout << "Center: (" << getPosition().x << ", " << getPosition().y << ")" << std::endl;
//	std::cout << "Fill Color: " << getFillColor() << std::endl;
//	std::cout << "Stroke Color: " << getOutlineColor() << std::endl;
//	std::cout << "Stroke Width: " << getOutlineThickness() << std::endl;
//}
//Vector2Df Circle::getMinBound() const {
//	Vector2Df radius = getRadius();
//	return Vector2Df(getPosition().x - radius.x, getPosition().y - radius.y);
//}
//Vector2Df Circle::getMaxBound() const {
//	Vector2Df radius = getRadius();
//	return Vector2Df(getPosition().x + radius.x, getPosition().y + radius.y);
//}
//void Circle::setRadius(float radius) {
//	MyEllipse::setRadius(Vector2Df(radius, radius));
//}
