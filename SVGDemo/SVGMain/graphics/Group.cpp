#include "Group.h"

Group::Group() {}

Group::Group(Attributes attributes) : attributes(attributes) {}

Group::~Group() {
    for (auto& shape : shapes) {
        delete shape;
    }
}

std::string Group::getClass() const { return "Group"; }

Attributes Group::getAttributes() const { return attributes; }

void Group::addElement(SVGElement* shape) {
    shapes.push_back(shape);
    shape->setParent(this);
}

std::vector< SVGElement* > Group::getElements() const { return shapes; }

void Group::printData() const {
   std::cout << "Group: " << std::endl;
   for (auto shape : shapes) {
       std::cout << "    ";
       shape->printData();
       std::cout << std::endl;
   }
}
Vector2Df Group::getMinBound() const {
    if (shapes.empty()) return Vector2Df(0, 0);
    Vector2Df minBound = shapes[0]->getMinBound();
    for (const auto& shape : shapes) {
        Vector2Df shapeMin = shape->getMinBound();
        if (shapeMin.x < minBound.x) minBound.x = shapeMin.x;
        if (shapeMin.y < minBound.y) minBound.y = shapeMin.y;
    }
    return minBound;
}
Vector2Df Group::getMaxBound() const {
    if (shapes.empty()) return Vector2Df(0, 0);
    Vector2Df maxBound = shapes[0]->getMaxBound();
    for (const auto& shape : shapes) {
        Vector2Df shapeMax = shape->getMaxBound();
        if (shapeMax.x > maxBound.x) maxBound.x = shapeMax.x;
        if (shapeMax.y > maxBound.y) maxBound.y = shapeMax.y;
    }
    return maxBound;
}
std::vector< std::string > Group::getTransforms() const {
    return SVGElement::getTransforms();
}
SVGElement* Group::getParent() const {
    return SVGElement::getParent();
}
//void Group::setGradient(Gradient* gradient) {
//    SVGElement::setGradient(gradient);
//}
//Gradient* Group::getGradient() const {
//    return SVGElement::getGradient();
//}