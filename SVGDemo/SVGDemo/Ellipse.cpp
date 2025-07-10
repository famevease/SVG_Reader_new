#include "stdafx.h"
#include "Ellipse.h"

Ellipse::Ellipse(const Vector2Df& radius, const Vector2Df& center, ColorShape fill, ColorShape stroke, float stroke_thickness): SVGElement(fill, stroke, stroke_thickness, center), radius(radius) {}

std::string Ellipse::getShape() const { 
    return "Ellipse"; 
}

void Ellipse::setRadius(const Vector2Df& radius) { 
    this->radius = radius; 
}

Vector2Df Ellipse::getRadius() const { 
    return radius; 
}

Vector2Df Ellipse::getMinBound() const {
    return Vector2Df(getPosition().x - getRadius().x, getPosition().y - getRadius().y);
}

Vector2Df Ellipse::getMaxBound() const {
    return Vector2Df(getPosition().x + getRadius().x, getPosition().y + getRadius().y);
}

//void Ellipse::printData() const {
//    SVGElement::printData();
//    std::cout << "Radius: " << getRadius().x << " " << getRadius().y << std::endl;
//}