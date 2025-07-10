#include "stdafx.h"
#include "Polygon.h"

Polygon::Polygon(ColorShape fill, ColorShape stroke, float stroke_width): PolyShape(fill, stroke, stroke_width) {}

std::string Polygon::getShape() const { 
    return "Polygon"; 
}