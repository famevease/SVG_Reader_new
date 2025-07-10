#include "stdafx.h"
#include "Rectangle.h"

Rectangle::Rectangle(float width, float height, Vector2Df position, Vector2Df radius, const ColorShape& fill, const ColorShape& stroke, float stroke_width): SVGElement(fill, stroke, stroke_width, position), width(width), height(height), radius(radius) {}

std::string Rectangle::getShape() const { 
	return "Rect"; 
}

void Rectangle::setWidth(float width) { 
	this->width = width; 
}

float Rectangle::getWidth() const { 
	return width; 
}

void Rectangle::setHeight(float height) { 
	this->height = height; 
}

float Rectangle::getHeight() const { 
	return height; 
}

void Rectangle::setRadius(const Vector2Df& radius) { 
	this->radius = radius; 
}

Vector2Df Rectangle::getRadius() const { 
	return radius; 
}

//void Rectangle::printData() const {
//    SVGElement::printData();
//    std::cout << "Width: " << getWidth() << std::endl;
//    std::cout << "Height: " << getHeight() << std::endl;
//    std::cout << "Radius: " << getRadius().x << " " << getRadius().y
//        << std::endl;
//}
