#include "stdafx.h"
#include "Polygon.h"

MyPolygon::MyPolygon(ColorShape fill, ColorShape stroke, float stroke_width): PolyShape(fill, stroke, stroke_width) {}

std::string MyPolygon::getClass() const { 
    return "Polygon"; 
}