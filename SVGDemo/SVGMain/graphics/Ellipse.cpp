#include "Ellipse.h"

MyEllipse::MyEllipse(const Vector2Df& radius, const Vector2Df& center, ColorShape fill, ColorShape stroke, float stroke_thickness): SVGElement(fill, stroke, stroke_thickness, center), radius(radius) {}

std::string MyEllipse::getClass() const { 
    return "Ellipse"; 
}

void MyEllipse::setRadius(const Vector2Df& radius) { 
    this->radius = radius; 
}

Vector2Df MyEllipse::getRadius() const { 
    return radius; 
}

Vector2Df MyEllipse::getMinBound() const {
    return Vector2Df(getPosition().x - getRadius().x, getPosition().y - getRadius().y);
}

Vector2Df MyEllipse::getMaxBound() const {
    return Vector2Df(getPosition().x + getRadius().x, getPosition().y + getRadius().y);
}

void MyEllipse::printData() const {
   SVGElement::printData();
   std::cout << "Radius: " << getRadius().x << " " << getRadius().y << std::endl;
}