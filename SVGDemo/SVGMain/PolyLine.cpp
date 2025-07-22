#include "stdafx.h"
#include "PolyLine.h"

MyPolyLine::MyPolyLine(const ColorShape& fill, const ColorShape& stroke, float stroke_width): PolyShape(fill, stroke, stroke_width) {}

std::string MyPolyLine::getClass() const { 
    return "Polyline"; 
}