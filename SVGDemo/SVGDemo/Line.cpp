#include "stdafx.h"
#include "Line.h"
#include <cmath>
using namespace std;

Line::Line(const Vector2Df& point1, const Vector2Df& point2, ColorShape stroke, float stroke_width): 
	SVGElement(ColorShape::Transparent, stroke, stroke_width, point1), direction(point2) {}

string Line::getShape() const {
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