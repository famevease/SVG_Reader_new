#include "stdafx.h"
#include "ColorShape.h"
using namespace std;

stroke::stroke() {
	this->strokeWidth = 1;
}

stroke::~stroke() {
	this->strokeWidth = 0;
}

ColorShape stroke::getStrokeColor() {
	return this->strokeColor;
}

float stroke::getStrokeWidth() {
	return this->strokeWidth;
}

void stroke::setStrokeColor(ColorShape strokeColor) {
	this->strokeColor = strokeColor;
}

void stroke::setStrokeWidth(float strokeWidth) {
	this->strokeWidth = strokeWidth;
}

