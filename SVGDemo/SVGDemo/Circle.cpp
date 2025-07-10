#include "stdafx.h"
#include "Circle.h"

Circle::Circle(float radius, const Vector2Df& center, ColorShape fill, ColorShape stroke, float stroke_width): Ellipse(Vector2Df(radius, radius), center, fill, stroke, stroke_width) {}

std::string Circle::getShape() const { 
	return "Circle"; 
}