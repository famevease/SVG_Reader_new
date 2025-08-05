#include "PolyLine.h"

MyPolyLine::MyPolyLine(const ColorShape& fill, const ColorShape& stroke, float stroke_width): MyPolyShape(fill, stroke, stroke_width) {}

std::string MyPolyLine::getClass() const { 
    return "Polyline"; 
}
std::vector<std::string> MyPolyLine::getTransforms() const {
    return SVGElement::getTransforms();
}
SVGElement* MyPolyLine::getParent() const {
    return SVGElement::getParent();
}
void MyPolyLine::addElement(SVGElement* element) {
    // Polylines do not support adding elements, so we can throw an exception or ignore
    throw std::runtime_error("Cannot add elements to a Polyline.");
}
// Gradient* MyPolyLine::getGradient() const {
//     return SVGElement::getGradient();
// }
// void MyPolyLine::setGradient(Gradient* gradient) {
//     SVGElement::setGradient(gradient);
// }
