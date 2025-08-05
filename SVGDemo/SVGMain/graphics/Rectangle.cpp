#include "Rectangle.h"

MyRectangle::MyRectangle(float width, float height, Vector2Df position, Vector2Df radius, const ColorShape& fill, const ColorShape& stroke, float stroke_width): SVGElement(fill, stroke, stroke_width, position), width(width), height(height), radius(radius) {}

std::string MyRectangle::getClass() const { 
	return "Rect"; 
}

void MyRectangle::setWidth(float width) { 
	this->width = width; 
}

float MyRectangle::getWidth() const { 
	return width; 
}

void MyRectangle::setHeight(float height) { 
	this->height = height; 
}

float MyRectangle::getHeight() const { 
	return height; 
}

void MyRectangle::setRadius(const Vector2Df& radius) { 
	this->radius = radius; 
}

Vector2Df MyRectangle::getRadius() const { 
	return radius; 
}

void MyRectangle::printData() const {
   SVGElement::printData();
   std::cout << "Width: " << getWidth() << std::endl;
   std::cout << "Height: " << getHeight() << std::endl;
   std::cout << "Radius: " << getRadius().x << " " << getRadius().y
       << std::endl;
}

Vector2Df MyRectangle::getMinBound() const {
	return Vector2Df(SVGElement::getPosition().x - radius.x, SVGElement::getPosition().y - radius.y);
}
Vector2Df MyRectangle::getMaxBound() const {
	return Vector2Df(SVGElement::getPosition().x + width + radius.x, SVGElement::getPosition().y + height + radius.y);
}
vector<string> MyRectangle::getTransforms() const {	
	return SVGElement::getTransforms();
}
SVGElement* MyRectangle::getParent() const {
	return SVGElement::getParent();
}
void MyRectangle::addElement(SVGElement* element) {
	// Rectangles do not support adding elements, so we can throw an exception or ignore
	throw std::runtime_error("Cannot add elements to a Rectangle.");
}
// Gradient* MyRectangle::getGradient() const {
//     return SVGElement::getGradient();
// }
// void MyRectangle::setGradient(Gradient* gradient) {
//     SVGElement::setGradient(gradient);
// }

