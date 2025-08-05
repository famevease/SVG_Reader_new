#include "Polygon.h"

MyPolygon::MyPolygon(ColorShape fill, ColorShape stroke, float stroke_width): MyPolyShape(fill, stroke, stroke_width) {}

std::string MyPolygon::getClass() const { 
    return "Polygon"; 
}
vector<string> MyPolygon::getTransforms() const {
    return SVGElement::getTransforms();
}
SVGElement* MyPolygon::getParent() const {
    return SVGElement::getParent();
}
void MyPolygon::addElement(SVGElement* element) {
    // Polygons do not support adding elements, so we can throw an exception or ignore
    throw std::runtime_error("Cannot add elements to a Polygon.");
}
// Gradient* MyPolygon::getGradient() const {
//     return SVGElement::getGradient();
// }
// void MyPolygon::setGradient(Gradient* gradient) {
//     SVGElement::setGradient(gradient);
// }
