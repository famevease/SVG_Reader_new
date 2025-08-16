#include "../graphics/Path.h"

Path::Path(const ColorShape& fill, const ColorShape& stroke, float stroke_width)
    : SVGElement(fill, stroke, stroke_width), fill_rule("nonzero") {
}

std::string Path::getClass() const { return "Path"; }

void Path::addPoint(PathPoint point) { points.push_back(point); }

std::vector< PathPoint > Path::getPoints() const { return points; }

void Path::setFillRule(std::string fill_rule) { this->fill_rule = fill_rule.empty() ? "nonzero" : fill_rule; }

std::string Path::getFillRule() const { return fill_rule; }

Vector2Df Path::getMinBound() const {
    if (points.empty()) return Vector2Df(0, 0);
    float minX = points[0].point.x;
    float minY = points[0].point.y;
    for (const auto& point : points) {
        if (point.point.x < minX) minX = point.point.x;
        if (point.point.y < minY) minY = point.point.y;
    }
    return Vector2Df(minX, minY);
}

Vector2Df Path::getMaxBound() const {
    if (points.empty()) return Vector2Df(0, 0);
    float maxX = points[0].point.x;
    float maxY = points[0].point.y;
    for (const auto& point : points) {
        if (point.point.x > maxX) maxX = point.point.x;
        if (point.point.y > maxY) maxY = point.point.y;
    }
    return Vector2Df(maxX, maxY);
}

void Path::printData() const {
    SVGElement::printData();
    std::cout << "Points: ";
    for (auto point : points) {
        std::cout << point.tc << " " << point.point.x << " " << point.point.y
            << " ";
    }
    std::cout << "\nFill Rule: " << fill_rule << "\n";
}

std::vector<std::string> Path::getTransforms() const {
    return SVGElement::getTransforms();
}

SVGElement* Path::getParent() const {
    return SVGElement::getParent();
}

void Path::addElement(SVGElement* element) {
    // Paths do not support adding elements, so we can throw an exception or ignore
    throw std::runtime_error("Cannot add elements to a Path.");
}

Gradient* Path::getGradient() const {
    return SVGElement::getGradient();
}

void Path::setGradient(Gradient* gradient) {
    SVGElement::setGradient(gradient);
}  
// For milestone 3, we will implement the gradient functionality
