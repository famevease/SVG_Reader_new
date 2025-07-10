#include "stdafx.h"
#include "PolyLine.h"

PolyLine::PolyLine(const ColorShape& fill, const ColorShape& stroke, float stroke_width): PolyShape(fill, stroke, stroke_width) {}

std::string PolyLine::getShape() const { 
    return "Polyline"; 
}