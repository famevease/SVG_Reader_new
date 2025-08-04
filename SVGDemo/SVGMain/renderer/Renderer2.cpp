#include "Renderer2.hpp"

#include <algorithm>
#include <codecvt>
#include <locale>

#include "../SVGElement.h"
#include "DrawShape.h"
#include "TransformUtils.h"

Renderer* Renderer::instance = nullptr;

Renderer::Renderer() {}

Renderer* Renderer::getInstance() {
    if (instance == nullptr) {
        instance = new Renderer();
    }
    return instance;
}

// Draw shapes within a group, considering transformations
void Renderer::draw(Gdiplus::Graphics& graphics, Group* group) const {
    for (auto shape : group->getElements()) {
        // Store the original transformation matrix
        Gdiplus::Matrix original;
        graphics.GetTransform(&original);

        // Apply the transformations for the current shape
        TransformUtils::applyTransform(shape->getTransforms(), graphics);

        // Draw the specific shape based on its class
        if (shape->getClass() == "Group") {
            Group* group = dynamic_cast< Group* >(shape);
            draw(graphics, group);
        } else if (shape->getClass() == "Polyline") {
            MyPolyLine* polyline = dynamic_cast< MyPolyLine* >(shape);
            drawPolyline(graphics, polyline);
        } else if (shape->getClass() == "Text") {
            Text* text = dynamic_cast< Text* >(shape);
            drawText(graphics, text);
        } else if (shape->getClass() == "Rectangle") {
            MyRectangle* rectangle = dynamic_cast<MyRectangle*>(shape);
            drawRectangle(graphics, rectangle);
        } else if (shape->getClass() == "Circle") {
            Circle* circle = dynamic_cast< Circle* >(shape);
            drawCircle(graphics, circle);
        } else if (shape->getClass() == "Ellipse") {
            MyEllipse* ellipse = dynamic_cast<MyEllipse* >(shape);
            drawEllipse(graphics, ellipse);
        } else if (shape->getClass() == "Line") {
            Line* line = dynamic_cast< Line* >(shape);
            drawLine(graphics, line);
        } else if (shape->getClass() == "Polygon") {
            MyPolygon* polygon = dynamic_cast< MyPolygon* >(shape);
            drawPolygon(graphics, polygon);
        } else if (shape->getClass() == "Path") {
            Path* path = dynamic_cast< Path* >(shape);
            drawPath(graphics, path);
        }
        graphics.SetTransform(&original);
    }
}
