#include "Renderer.hpp"

#include <algorithm>
#include <codecvt>
#include <locale>

Renderer* Renderer::instance = nullptr;

Renderer::Renderer() {}

Renderer* Renderer::getInstance() {
    if (instance == nullptr) {
        instance = new Renderer();
    }
    return instance;
}

// Function to extract translation values from a transform string
std::pair< float, float > getTranslate(std::string transform_value) {
    float trans_x = 0, trans_y = 0;
    if (transform_value.find(",") != std::string::npos) {
        sscanf_s(transform_value.c_str(), "translate(%f, %f)", &trans_x,
               &trans_y);
    } else {
        sscanf_s(transform_value.c_str(), "translate(%f %f)", &trans_x, &trans_y);
    }
    return std::pair< float, float >(trans_x, trans_y);
}

// Function to extract rotation value from a transform string
float getRotate(std::string transform_value) {
    float degree = 0;
    sscanf_s(transform_value.c_str(), "rotate(%f)", &degree);
    return degree;
}

// Function to extract scale value from a transform string
float getScale(std::string transform_value) {
    float scale = 0;
    sscanf_s(transform_value.c_str(), "scale(%f)", &scale);
    return scale;
}

// Function to extract X and Y scale values from a transform string
std::pair< float, float > getScaleXY(std::string transform_value) {
    float scale_x = 0, scale_y = 0;
    if (transform_value.find(",") != std::string::npos)
        sscanf_s(transform_value.c_str(), "scale(%f, %f)", &scale_x, &scale_y);
    else
        sscanf_s(transform_value.c_str(), "scale(%f %f)", &scale_x, &scale_y);
    return std::pair< float, float >(scale_x, scale_y);
}

// Apply transformations based on the specified order
void Renderer::applyTransform(std::vector< std::string > transform_order,
                              Gdiplus::Graphics& graphics) const {
    for (auto type : transform_order) {
        if (type.find("translate") != std::string::npos) {
            float trans_x = getTranslate(type).first,
                  trans_y = getTranslate(type).second;
            graphics.TranslateTransform(trans_x, trans_y);
        } else if (type.find("rotate") != std::string::npos) {
            float degree = getRotate(type);
            graphics.RotateTransform(degree);
        } else if (type.find("scale") != std::string::npos) {
            if (type.find(",") != std::string::npos) {
                float scale_x = getScaleXY(type).first,
                      scale_y = getScaleXY(type).second;
                graphics.ScaleTransform(scale_x, scale_y);
            } else {
                float scale = getScale(type);
                graphics.ScaleTransform(scale, scale);
            }
        }
    }
}

// Draw shapes within a group, considering transformations
void Renderer::draw(Gdiplus::Graphics& graphics, Group* group) const {
    for (auto shape : group->getElements()) {
        // Store the original transformation matrix
        Gdiplus::Matrix original;
        graphics.GetTransform(&original);

        // Apply the transformations for the current shape
        applyTransform(shape->getTransforms(), graphics);

        // Draw the specific shape based on its class
        if (shape->getClass() == "Group") {
            Group* group = dynamic_cast< Group* >(shape);
            draw(graphics, group);
        } else if (shape->getClass() == "Polyline") {
            Plyline* polyline = dynamic_cast< Plyline* >(shape);
            drawPolyline(graphics, polyline);
        } else if (shape->getClass() == "Text") {
            Text* text = dynamic_cast< Text* >(shape);
            drawText(graphics, text);
        } else if (shape->getClass() == "Rect") {
            Rect* rectangle = dynamic_cast< Rect* >(shape);
            drawRectangle(graphics, rectangle);
        } else if (shape->getClass() == "Circle") {
            Circle* circle = dynamic_cast< Circle* >(shape);
            drawCircle(graphics, circle);
        } else if (shape->getClass() == "Ellipse") {
            Ell* ellipse = dynamic_cast< Ell* >(shape);
            drawEllipse(graphics, ellipse);
        } else if (shape->getClass() == "Line") {
            Line* line = dynamic_cast< Line* >(shape);
            drawLine(graphics, line);
        } else if (shape->getClass() == "Polygon") {
            Plygon* polygon = dynamic_cast< Plygon* >(shape);
            drawPolygon(graphics, polygon);
        } else if (shape->getClass() == "Path") {
            Path* path = dynamic_cast< Path* >(shape);
            drawPath(graphics, path);
        }
        graphics.SetTransform(&original);
    }
}

// Draw a line on the given graphics context
void Renderer::drawLine(Gdiplus::Graphics& graphics, Line* line) const {
    // Extract color and thickness information from the Line object
    ColorShape color = line->getOutlineColor();
    Gdiplus::Pen linePen(Gdiplus::Color(color.a, color.r, color.g, color.b),
                         line->getOutlineThickness());
    // Extract start and end points from the Line object
    Gdiplus::PointF startPoint(line->getPosition().x, line->getPosition().y);
    Gdiplus::PointF endPoint(line->getDirection().x, line->getDirection().y);
    graphics.DrawLine(&linePen, startPoint, endPoint);
}

// Draw a rectangle on the given graphics context
void Renderer::drawRectangle(Gdiplus::Graphics& graphics,
                             Rect* rectangle) const {
    float x = rectangle->getPosition().x;
    float y = rectangle->getPosition().y;
    float width = rectangle->getWidth();
    float height = rectangle->getHeight();
    ColorShape outline_color = rectangle->getOutlineColor();

    // Create a pen for the rectangle outline
    Gdiplus::Pen rect_outline(Gdiplus::Color(outline_color.a, outline_color.r,
                                             outline_color.g, outline_color.b),
                              rectangle->getOutlineThickness());
    Gdiplus::RectF bound(x, y, width, height);
    Gdiplus::Brush* rect_fill = getBrush(rectangle, bound);

    // Check if the rectangle has rounded corners
    if (rectangle->getRadius().x != 0 || rectangle->getRadius().y != 0) {
        float dx = rectangle->getRadius().x * 2;
        float dy = rectangle->getRadius().y * 2;

        // Create a GraphicsPath for drawing rounded rectangles
        Gdiplus::GraphicsPath path;
        path.AddArc(x, y, dx, dy, 180, 90);
        path.AddArc(x + width - dx, y, dx, dy, 270, 90);
        path.AddArc(x + width - dx, y + height - dy, dx, dy, 0, 90);
        path.AddArc(x, y + height - dy, dx, dy, 90, 90);
        path.CloseFigure();
        // Fill and draw the rounded rectangle
        if (Gdiplus::PathGradientBrush* brush =
                dynamic_cast< Gdiplus::PathGradientBrush* >(rect_fill)) {
            ColorShape color =
                rectangle->getGradient()->getStops().back().getColor();
            Gdiplus::SolidBrush corner_fill(
                Gdiplus::Color(color.a, color.r, color.g, color.b));
            graphics.FillPath(&corner_fill, &path);
        }

        graphics.FillPath(rect_fill, &path);
        graphics.DrawPath(&rect_outline, &path);
    } else {
        // Fill and draw the regular rectangle
        if (Gdiplus::PathGradientBrush* brush =
                dynamic_cast< Gdiplus::PathGradientBrush* >(rect_fill)) {
            ColorShape color =
                rectangle->getGradient()->getStops().back().getColor();
            Gdiplus::SolidBrush corner_fill(
                Gdiplus::Color(color.a, color.r, color.g, color.b));
            graphics.FillRectangle(&corner_fill, x, y, width, height);
        }

        graphics.FillRectangle(rect_fill, x, y, width, height);
        graphics.DrawRectangle(&rect_outline, x, y, width, height);
    }

    delete rect_fill;
}

// Draw a circle on the given graphics context
void Renderer::drawCircle(Gdiplus::Graphics& graphics, Circle* circle) const {
    ColorShape outline_color = circle->getOutlineColor();
    Gdiplus::Pen circle_outline(
        Gdiplus::Color(outline_color.a, outline_color.r, outline_color.g,
                       outline_color.b),
        circle->getOutlineThickness());

    // Create a bounding rectangle for the circle
    Vector2Df min_bound = circle->getMinBound();
    Vector2Df max_bound = circle->getMaxBound();
    Gdiplus::RectF bound(min_bound.x, min_bound.y, max_bound.x - min_bound.x,
                         max_bound.y - min_bound.y);
    Gdiplus::Brush* circle_fill = getBrush(circle, bound);

    // Check if the circle has a gradient fill
    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(circle_fill)) {
        ColorShape color = circle->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(
            Gdiplus::Color(color.a, color.r, color.g, color.b));
        graphics.FillEllipse(
            &corner_fill, circle->getPosition().x - circle->getRadius().x,
            circle->getPosition().y - circle->getRadius().y,
            circle->getRadius().x * 2, circle->getRadius().y * 2);
    }

    graphics.FillEllipse(circle_fill,
                         circle->getPosition().x - circle->getRadius().x,
                         circle->getPosition().y - circle->getRadius().y,
                         circle->getRadius().x * 2, circle->getRadius().y * 2);
    graphics.DrawEllipse(&circle_outline,
                         circle->getPosition().x - circle->getRadius().x,
                         circle->getPosition().y - circle->getRadius().y,
                         circle->getRadius().x * 2, circle->getRadius().x * 2);

    delete circle_fill;
}

// Draw an ellipse on the given graphics context
void Renderer::drawEllipse(Gdiplus::Graphics& graphics, Ell* ellipse) const {
    ColorShape outline_color = ellipse->getOutlineColor();

    Gdiplus::Pen ellipse_outline(
        Gdiplus::Color(outline_color.a, outline_color.r, outline_color.g,
                       outline_color.b),
        ellipse->getOutlineThickness());

    // Create a bounding rectangle for the ellipse
    Vector2Df min_bound = ellipse->getMinBound();
    Vector2Df max_bound = ellipse->getMaxBound();
    Gdiplus::RectF bound(min_bound.x, min_bound.y, max_bound.x - min_bound.x,
                         max_bound.y - min_bound.y);
    Gdiplus::Brush* ellipse_fill = getBrush(ellipse, bound);

    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(ellipse_fill)) {
        ColorShape color = ellipse->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(
            Gdiplus::Color(color.a, color.r, color.g, color.b));
        graphics.FillEllipse(
            &corner_fill, ellipse->getPosition().x - ellipse->getRadius().x,
            ellipse->getPosition().y - ellipse->getRadius().y,
            ellipse->getRadius().x * 2, ellipse->getRadius().y * 2);
    }

    graphics.FillEllipse(
        ellipse_fill, ellipse->getPosition().x - ellipse->getRadius().x,
        ellipse->getPosition().y - ellipse->getRadius().y,
        ellipse->getRadius().x * 2, ellipse->getRadius().y * 2);
    graphics.DrawEllipse(
        &ellipse_outline, ellipse->getPosition().x - ellipse->getRadius().x,
        ellipse->getPosition().y - ellipse->getRadius().y,
        ellipse->getRadius().x * 2, ellipse->getRadius().y * 2);

    delete ellipse_fill;
}

