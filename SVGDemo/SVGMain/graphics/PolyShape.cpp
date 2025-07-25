#include "stdafx.h"
#include "PolyShape.h"

MyPolyShape::MyPolyShape(const ColorShape& fill, const ColorShape& stroke, float stroke_width): SVGElement(fill, stroke, stroke_width) {}

void MyPolyShape::addPoint(const Vector2Df& point) { 
    points.push_back(point); 
}

const std::vector< Vector2Df >& MyPolyShape::getPoints() const { 
    return points; 
}

void MyPolyShape::setFillRule(std::string fill_rule) {
    this->fill_rule = fill_rule;
}

std::string MyPolyShape::getFillRule() const { 
    return fill_rule; 
}

Vector2Df MyPolyShape::getMinBound() const {
    float min_x = points[0].x;
    float min_y = points[0].y;
    for (auto& point : points) {
        min_x = min_x < point.x ? min_x : point.x;
        min_y = min_y < point.y ? min_y : point.y;
    }
    return Vector2Df(min_x, min_y);
}

Vector2Df MyPolyShape::getMaxBound() const {
    float max_x = points[0].x;
    float max_y = points[0].y;
    for (auto& point : points) {
        max_x = max_x > point.x ? max_x : point.x;
        max_y = max_y > point.y ? max_y : point.y;
    }
    return Vector2Df(max_x, max_y);
}

//void PolyShape::printData() const {
//    SVGElement::printData();
//    std::cout << "Points: ";
//    for (auto& point : getPoints()) {
//        std::cout << point.x << "," << point.y << " ";
//    }
//    std::cout << std::endl;
//}
