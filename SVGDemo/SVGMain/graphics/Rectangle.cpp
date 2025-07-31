#include "stdafx.h"
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
