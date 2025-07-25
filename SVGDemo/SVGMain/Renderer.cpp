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

// Draw a line on the given graphics context
void Renderer::drawLine(Gdiplus::Graphics& graphics, Line* line) const {
    // Extract color and thickness information from the Line object
    ColorShape color = line->getOutlineColor();
    Gdiplus::Pen linePen(color.toGDIColor(),
                         line->getOutlineThickness());
    // Extract start and end points from the Line object
    Gdiplus::PointF startPoint(line->getPosition().x, line->getPosition().y);
    Gdiplus::PointF endPoint(line->getDirection().x, line->getDirection().y);
    graphics.DrawLine(&linePen, startPoint, endPoint);
}

// Draw a rectangle on the given graphics context
void Renderer::drawRectangle(Gdiplus::Graphics& graphics,
                             MyRectangle* rectangle) const {
    float x = rectangle->getPosition().x;
    float y = rectangle->getPosition().y;
    float width = rectangle->getWidth();
    float height = rectangle->getHeight();
    ColorShape outline_color = rectangle->getOutlineColor();

    // Create a pen for the rectangle outline
    Gdiplus::Pen rect_outline(outline_color.toGDIColor(),
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
                color.toGDIColor());
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
                color.toGDIColor());
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
        outline_color.toGDIColor(),
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
            color.toGDIColor());
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
void Renderer::drawEllipse(Gdiplus::Graphics& graphics, MyEllipse* ellipse) const {
    ColorShape outline_color = ellipse->getOutlineColor();

    Gdiplus::Pen ellipse_outline(
        outline_color.toGDIColor(),
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
            color.toGDIColor());
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

// Draw a polygon on the given graphics context
void Renderer::drawPolygon(Gdiplus::Graphics& graphics, MyPolygon* polygon) const {
    ColorShape outline_color = polygon->getOutlineColor();
    Gdiplus::Pen polygon_outline(
        Gdiplus::Color(outline_color.getA(), outline_color.getR(), outline_color.getG(),
                       outline_color.getB()),
        polygon->getOutlineThickness());

    // Extract vertices and create an array of Gdiplus::PointF
    Gdiplus::PointF* points = new Gdiplus::PointF[polygon->getPoints().size()];
    int idx = 0;
    const std::vector< Vector2Df >& vertices = polygon->getPoints();
    for (const Vector2Df vertex : vertices) {
        points[idx++] = Gdiplus::PointF(vertex.x, vertex.y);
    }

    // Determine the fill mode based on the polygon's fill rule
    Gdiplus::FillMode fill_mode;
    if (polygon->getFillRule() == "evenodd") {
        fill_mode = Gdiplus::FillModeAlternate;
    } else if (polygon->getFillRule() == "nonzero") {
        fill_mode = Gdiplus::FillModeWinding;
    }

    // Create a bounding rectangle for the polygon
    Vector2Df min_bound = polygon->getMinBound();
    Vector2Df max_bound = polygon->getMaxBound();
    Gdiplus::RectF bound(min_bound.x, min_bound.y, max_bound.x - min_bound.x,
                         max_bound.y - min_bound.y);
    // Get the fill brush for the polygon
    Gdiplus::Brush* polygon_fill = getBrush(polygon, bound);

    // If the fill brush is a gradient, fill the polygon with a corner color
    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(polygon_fill)) {
        ColorShape color = polygon->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(
            Gdiplus::Color(color.getA(), color.getR(), color.getG(), color.getB()));
        graphics.FillPolygon(&corner_fill, points, idx, fill_mode);
    }

    graphics.FillPolygon(polygon_fill, points, idx, fill_mode);
    graphics.DrawPolygon(&polygon_outline, points, idx);

    delete[] points;
    delete polygon_fill;
}

// Draw a polyline on the given graphics context
void Renderer::drawPolyline(Gdiplus::Graphics& graphics,
                            MyPolyLine* polyline) const {
    ColorShape outline_color = polyline->getOutlineColor();
    Gdiplus::Pen polyline_outline(
        Gdiplus::Color(outline_color.getA(), outline_color.getR(), outline_color.getG(),
                       outline_color.getB()),
        polyline->getOutlineThickness());

    // Determine the fill mode based on the polyline's fill rule
    Gdiplus::FillMode fill_mode;
    if (polyline->getFillRule() == "evenodd") {
        fill_mode = Gdiplus::FillModeAlternate;
    } else if (polyline->getFillRule() == "nonzero") {
        fill_mode = Gdiplus::FillModeWinding;
    }

    Gdiplus::GraphicsPath path(fill_mode);
    const std::vector< Vector2Df >& points = polyline->getPoints();
    if (points.size() < 2) {
        return;
    }

    path.StartFigure();
    path.AddLine(points[0].x, points[0].y, points[1].x, points[1].y);
    for (size_t i = 2; i < points.size(); ++i) {
        path.AddLine(points[i - 1].x, points[i - 1].y, points[i].x,
                     points[i].y);
    }

    // Create a bounding rectangle for the polyline
    Vector2Df min_bound = polyline->getMinBound();
    Vector2Df max_bound = polyline->getMaxBound();
    Gdiplus::RectF bound(min_bound.x, min_bound.y, max_bound.x - min_bound.x,
                         max_bound.y - min_bound.y);
    Gdiplus::Brush* polyline_fill = getBrush(polyline, bound);

    // If the fill brush is a gradient, fill the polyline with a corner color
    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(polyline_fill)) {
        ColorShape color =
            polyline->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(
            Gdiplus::Color(color.getA(), color.getR(), color.getG(), color.getB()));
        graphics.FillPath(&corner_fill, &path);
    }

    graphics.FillPath(polyline_fill, &path);
    graphics.DrawPath(&polyline_outline, &path);

    delete polyline_fill;
}

// Draw text on the given graphics context
void Renderer::drawText(Gdiplus::Graphics& graphics, Text* text) const {
    ColorShape outline_color = text->getOutlineColor();
    graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);

    Gdiplus::Pen text_outline(Gdiplus::Color(outline_color.getA(), outline_color.getR(),
                                             outline_color.getG(), outline_color.getB()),
                              text->getOutlineThickness());

    // Set the font family for the text
    Gdiplus::FontFamily font_family(L"Times New Roman");

    // Set the position for the text
    Gdiplus::PointF position(text->getPosition().x, text->getPosition().y);
    Gdiplus::GraphicsPath path;

    // Convert the content to wide string for GDI+
    std::wstring_convert< std::codecvt_utf8_utf16< wchar_t > > converter;
    std::wstring wide_content = converter.from_bytes(text->getContent());

    // Set text alignment based on anchor position
    Gdiplus::StringFormat string_format;
    if (text->getAnchor() == "middle") {
        string_format.SetAlignment(Gdiplus::StringAlignmentCenter);
        position.X += 7;
    } else if (text->getAnchor() == "end") {
        string_format.SetAlignment(Gdiplus::StringAlignmentFar);
        position.X += 14;
    } else {
        string_format.SetAlignment(Gdiplus::StringAlignmentNear);
    }

    // Set font style based on text style
    Gdiplus::FontStyle font_style = Gdiplus::FontStyleRegular;
    if (text->getFontStyle() == "italic" || text->getFontStyle() == "oblique") {
        font_style = Gdiplus::FontStyleItalic;
        position.Y -= 1;
    }

    path.AddString(wide_content.c_str(), wide_content.size(), &font_family,
                   font_style, text->getFontSize(), position, &string_format);
    Gdiplus::RectF bound;
    path.GetBounds(&bound);
    Gdiplus::Brush* text_fill = getBrush(text, bound);

    // If the fill brush is a gradient, fill the text with a corner color
    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(text_fill)) {
        ColorShape color = text->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(
            Gdiplus::Color(color.getA(), color.getR(), color.getG(), color.getB()));
        graphics.FillPath(&corner_fill, &path);
    }

    graphics.FillPath(text_fill, &path);
    if (text->getOutlineColor().getA() != 0 &&
        text->getOutlineColor().getA() == text->getFillColor().getA()) {
        text_outline.SetColor(Gdiplus::Color(255, 255, 255, 255));
        graphics.DrawPath(&text_outline, &path);
        text_outline.SetColor(Gdiplus::Color(outline_color.getA(), outline_color.getR(),
                                             outline_color.getG(), outline_color.getB()));
    }
    graphics.DrawPath(&text_outline, &path);

    delete text_fill;
}

// Draw a path on the given graphics context
void Renderer::drawPath(Gdiplus::Graphics& graphics, Path* path) const {
    ColorShape outline_color = path->getOutlineColor();
    Gdiplus::Pen path_outline(Gdiplus::Color(outline_color.getA(), outline_color.getR(),
                                             outline_color.getG(), outline_color.getB()),
                              path->getOutlineThickness());

    // Fill the path by rules
    Gdiplus::FillMode fill_mode;
    if (path->getFillRule() == "evenodd") {
        fill_mode = Gdiplus::FillModeAlternate;
    } else if (path->getFillRule() == "nonzero") {
        fill_mode = Gdiplus::FillModeWinding;
    }
    Gdiplus::GraphicsPath gdi_path(fill_mode);

    const std::vector< PathPoint >& points = path->getPoints();
    int n = points.size();
    Vector2Df first_point{0, 0}, cur_point{0, 0};

    // Construct the path
    for (int i = 0; i < n; ++i) {
        if (points[i].tc == 'm') {
            // If the command is m, then start a new figure
            first_point = points[i].point;
            gdi_path.StartFigure();
            cur_point = first_point;
        } else if (points[i].tc == 'l' || points[i].tc == 'h' ||
                   points[i].tc == 'v') {
            // If the command is l, h, or v, then add a line to the path
            gdi_path.AddLine(cur_point.x, cur_point.y, points[i].point.x,
                             points[i].point.y);
            cur_point = points[i].point;
        } else if (points[i].tc == 'c') {
            // If the command is c, then add a bezier curve to the path
            if (i + 2 < n) {
                Vector2Df control_point1 = points[i].point;
                Vector2Df control_point2 = points[i + 1].point;
                Vector2Df control_point3 = points[i + 2].point;
                gdi_path.AddBezier(cur_point.x, cur_point.y, control_point1.x,
                                   control_point1.y, control_point2.x,
                                   control_point2.y, control_point3.x,
                                   control_point3.y);
                i += 2;
                cur_point = control_point3;
            }
        } else if (points[i].tc == 'z') {
            // If the command is z, then close the figure
            gdi_path.CloseFigure();
            cur_point = first_point;
        } else if (points[i].tc == 's') {
            // If the command is s, then add a bezier curve to the path
            if (i + 1 < n) {
                // Calculate the first control point
                Vector2Df auto_control_point;
                if (i > 0 &&
                    (points[i - 1].tc == 'c' || points[i - 1].tc == 's')) {
                    auto_control_point.x =
                        cur_point.x * 2 - points[i - 2].point.x;
                    auto_control_point.y =
                        cur_point.y * 2 - points[i - 2].point.y;
                } else {
                    auto_control_point = cur_point;
                }
                // Calculate the rest control points
                Vector2Df control_point2 = points[i].point;
                Vector2Df control_point3 = points[i + 1].point;
                gdi_path.AddBezier(cur_point.x, cur_point.y,
                                   auto_control_point.x, auto_control_point.y,
                                   control_point2.x, control_point2.y,
                                   control_point3.x, control_point3.y);
                i += 1;
                cur_point = control_point3;
            }
        } else if (points[i].tc == 'q') {
            // If the command is q, then add a quadratic bezier curve to the
            if (i + 1 < n) {
                // Calculate the control point and its end point
                Vector2Df control_point = points[i].point;
                Vector2Df end_point = points[i + 1].point;

                // Add the curve to the path
                Gdiplus::PointF q_points[3];
                q_points[0] = Gdiplus::PointF{cur_point.x, cur_point.y};
                q_points[1] = Gdiplus::PointF{control_point.x, control_point.y};
                q_points[2] = Gdiplus::PointF{end_point.x, end_point.y};
                gdi_path.AddCurve(q_points, 3);
                cur_point = points[i + 1].point;
                i += 1;
            }
        } else if (points[i].tc == 't') {
            // Calculate reflection control point
            Vector2Df auto_control_point;
            if (i > 0 && (points[i - 1].tc == 'q' || points[i - 1].tc == 't')) {
                // If the previous point is a quadratic bezier or a smooth
                // quadratic bezier,
                // calculate the reflection control point using the reflection
                // formula
                auto_control_point.x = cur_point.x * 2 - points[i - 2].point.x;
                auto_control_point.y = cur_point.y * 2 - points[i - 2].point.y;
            } else {
                // Otherwise, use the current point as the control point
                auto_control_point = cur_point;
            }
            Vector2Df end_point = points[i].point;
            Gdiplus::PointF t_points[3];
            t_points[0] = Gdiplus::PointF{cur_point.x, cur_point.y};
            t_points[1] =
                Gdiplus::PointF{auto_control_point.x, auto_control_point.y};
            t_points[2] = Gdiplus::PointF{end_point.x, end_point.y};
            // Add the cubic bezier curve to the path
            gdi_path.AddCurve(t_points, 3);
            cur_point = points[i].point;
        } else if (points[i].tc == 'a') {
            float rx = points[i].radius.x;
            float ry = points[i].radius.y;
            // If either radius is zero, treat it as a line segment
            if (rx == 0 || ry == 0) {
                gdi_path.AddLine(cur_point.x, cur_point.y, points[i].point.x,
                                 points[i].point.y);
                cur_point = points[i].point;
                continue;
            }
            if (rx < 0) {
                rx = std::fabs(rx);
            }
            if (ry < 0) {
                ry = std::fabs(ry);
            }

            float x_axis_rotation = points[i].x_axis_rotation;
            bool large_arc_flag = points[i].large_arc_flag;
            bool sweep_flag = points[i].sweep_flag;
            Vector2Df end_point{points[i].point.x, points[i].point.y};
            // Calculate angles and points for the elliptical arc
            float angle = x_axis_rotation * acos(-1) / 180.0;
            float cosAngle = cos(angle);
            float sinAngle = sin(angle);

            Vector2Df point1;
            float X = (cur_point.x - end_point.x) / 2.0;
            float Y = (cur_point.y - end_point.y) / 2.0;
            point1.x = (cosAngle * cosAngle + sinAngle * sinAngle) * X;
            point1.y = (cosAngle * cosAngle + sinAngle * sinAngle) * Y;
            // Correction of out-of-range radii
            float radii_check = (point1.x * point1.x) / (rx * rx) +
                                (point1.y * point1.y) / (ry * ry);
            if (radii_check > 1.0) {
                rx = std::sqrt(radii_check) * rx;
                ry = std::sqrt(radii_check) * ry;
            }

            float sign = (large_arc_flag == sweep_flag ? -1.0 : 1.0);
            Vector2Df point2;
            float numo = (rx * rx) * (ry * ry) -
                         (rx * rx) * (point1.y * point1.y) -
                         (ry * ry) * (point1.x * point1.x);
            float deno = (rx * rx) * (point1.y * point1.y) +
                         (ry * ry) * (point1.x * point1.x);

            if (numo < 0) {
                numo = std::fabs(numo);
            }

            point2.x = sign * std::sqrt(numo / deno) * ((rx * point1.y) / ry);
            point2.y = sign * std::sqrt(numo / deno) * ((-ry * point1.x) / rx);

            Vector2Df center;
            X = (cur_point.x + end_point.x) / 2.0;
            Y = (cur_point.y + end_point.y) / 2.0;
            center.x =
                (cosAngle * cosAngle + sinAngle * sinAngle) * point2.x + X;
            center.y =
                (cosAngle * cosAngle + sinAngle * sinAngle) * point2.y + Y;

            float start_angle =
                atan2((point1.y - point2.y) / ry, (point1.x - point2.x) / rx);
            float end_angle =
                atan2((-point1.y - point2.y) / ry, (-point1.x - point2.x) / rx);

            float delta_angle = end_angle - start_angle;

            if (sweep_flag && delta_angle < 0) {
                delta_angle += 2.0 * acos(-1);
            } else if (!sweep_flag && delta_angle > 0) {
                delta_angle -= 2.0 * acos(-1);
            }

            float start_angle_degree =
                std::fmod((start_angle * 180.0) / acos(-1), 360);
            float delta_angle_degree =
                std::fmod((delta_angle * 180.0) / acos(-1), 360);
            // Add the elliptical arc to the path
            gdi_path.AddArc(center.x - rx, center.y - ry, 2.0 * rx, 2.0 * ry,
                            start_angle_degree, delta_angle_degree);

            cur_point = end_point;
        }
    }

    Gdiplus::RectF bound;
    gdi_path.GetBounds(&bound);
    Gdiplus::Brush* path_fill = getBrush(path, bound);
    Gdiplus::Region region(&gdi_path);

    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(path_fill)) {
        ColorShape color = path->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(
            Gdiplus::Color(color.getA(), color.getR(), color.getG(), color.getB()));

        if (path->getGradient()->getUnits() == "userSpaceOnUse") {
            float cx = path->getGradient()->getPoints().first.x;
            float cy = path->getGradient()->getPoints().first.y;
            float r = dynamic_cast< RadialGradient* >(path->getGradient())
                          ->getRadius()
                          .x;
            Gdiplus::GraphicsPath fill_path(fill_mode);
            fill_path.AddEllipse(cx - r, cy - r, 2 * r, 2 * r);

            for (auto type : path->getGradient()->getTransforms()) {
                if (type.find("matrix") != std::string::npos) {
                    float a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
                    if (type.find(",") != std::string::npos) {
                        type.erase(std::remove(type.begin(), type.end(), ','),
                                   type.end());
                    }
                    sscanf_s(type.c_str(), "matrix(%f %f %f %f %f %f)", &a, &b,
                           &c, &d, &e, &f);
                    Gdiplus::Matrix matrix(a, b, c, d, e, f);
                    fill_path.Transform(&matrix);
                }
            }
            region.Exclude(&fill_path);
        }
        graphics.FillRegion(&corner_fill, &region);
    }

    graphics.FillPath(path_fill, &gdi_path);
    graphics.DrawPath(&path_outline, &gdi_path);

    delete path_fill;
}

// Get the Gdiplus::Brush for rendering an SVG element (shape) with a gradient
// or solid color
Gdiplus::Brush* Renderer::getBrush(SVGElement* shape,
                                   Gdiplus::RectF bound) const {
    Gradient* gradient = shape->getGradient();
    if (gradient != NULL) {
        std::pair< Vector2Df, Vector2Df > points = gradient->getPoints();
        std::vector< Stop > stops = gradient->getStops();
        int stop_size = stops.size() + 2;
        Gdiplus::Color* colors = new Gdiplus::Color[stop_size];
        float* offsets = new float[stop_size];

        if (gradient->getClass() == "LinearGradient") {
            // Brush linear gradient
            if (gradient->getUnits() == "objectBoundingBox") {
                points.first.x = bound.X;
                points.first.y = bound.Y;
                points.second.x = bound.X + bound.Width;
                points.second.y = bound.Y + bound.Height;
            }

            // Set the center color
            offsets[0] = 0;
            offsets[stop_size - 1] = 1;
            colors[0] =
                Gdiplus::Color(stops[0].getColor().getA(), stops[0].getColor().getR(),
                               stops[0].getColor().getG(), stops[0].getColor().getB());
            colors[stop_size - 1] =
                Gdiplus::Color(stops[stop_size - 3].getColor().getA(),
                               stops[stop_size - 3].getColor().getR(),
                               stops[stop_size - 3].getColor().getG(),
                               stops[stop_size - 3].getColor().getB());

            // Reverse the order of the stops
            for (size_t i = 1; i < stop_size - 1; ++i) {
                colors[i] = Gdiplus::Color(
                    stops[i - 1].getColor().getA(), stops[i - 1].getColor().getR(),
                    stops[i - 1].getColor().getG(), stops[i - 1].getColor().getB());
                offsets[i] = stops[i - 1].getOffset();
            }

            // Create the brush of linear gradient
            Gdiplus::LinearGradientBrush* fill =
                new Gdiplus::LinearGradientBrush(
                    Gdiplus::PointF(points.first.x, points.first.y),
                    Gdiplus::PointF(points.second.x, points.second.y),
                    colors[0], colors[stop_size - 1]);
            fill->SetWrapMode(Gdiplus::WrapModeTileFlipX);
            fill->SetInterpolationColors(colors, offsets, stop_size);
            applyTransformsOnBrush(gradient->getTransforms(), fill);

            delete[] colors;
            delete[] offsets;
            return fill;
        } else if (gradient->getClass() == "RadialGradient") {
            // Brush radiol gradient
            RadialGradient* radial_gradient =
                dynamic_cast< RadialGradient* >(gradient);
            Vector2Df radius = radial_gradient->getRadius();

            // If the gradient is in userSpaceOnUse, the radius is the distance
            if (gradient->getUnits() == "userSpaceOnUse") {
                bound.X = points.first.x - radius.x;
                bound.Y = points.first.y - radius.x;
                bound.Width = radius.x * 2;
                bound.Height = radius.x * 2;
            }

            Gdiplus::GraphicsPath path;
            path.AddEllipse(bound);
            Gdiplus::PathGradientBrush* fill =
                new Gdiplus::PathGradientBrush(&path);

            // Set the center color
            offsets[0] = 0;
            offsets[stop_size - 1] = 1;
            colors[0] = Gdiplus::Color(stops[stop_size - 3].getColor().getA(),
                                       stops[stop_size - 3].getColor().getR(),
                                       stops[stop_size - 3].getColor().getG(),
                                       stops[stop_size - 3].getColor().getB());
            colors[stop_size - 1] =
                Gdiplus::Color(stops[0].getColor().getA(), stops[0].getColor().getR(),
                               stops[0].getColor().getG(), stops[0].getColor().getB());

            // Reverse the order of the stops
            for (size_t i = 1; i < stop_size - 1; ++i) {
                colors[i] =
                    Gdiplus::Color(stops[stop_size - 2 - i].getColor().getA(),
                                   stops[stop_size - 2 - i].getColor().getR(),
                                   stops[stop_size - 2 - i].getColor().getG(),
                                   stops[stop_size - 2 - i].getColor().getB());
                offsets[i] = 1 - stops[stop_size - 2 - i].getOffset();
            }

            fill->SetInterpolationColors(colors, offsets, stop_size);
            applyTransformsOnBrush(gradient->getTransforms(), fill);
            delete[] colors;
            delete[] offsets;
            return fill;
        }
    } else {
        ColorShape color = shape->getFillColor();
        Gdiplus::SolidBrush* fill = new Gdiplus::SolidBrush(
            Gdiplus::Color(color.getA(), color.getR(), color.getG(), color.getB()));
        return fill;
    }
    return nullptr;
}

// Apply transformation matrix operations on a linear gradient brush
void Renderer::applyTransformsOnBrush(
    std::vector< std::string > transform_order,
    Gdiplus::LinearGradientBrush*& brush) const {
    for (auto type : transform_order) {
        if (type.find("translate") != std::string::npos) {
            // Apply translation transformation
            float trans_x = getTranslate(type).first,
                  trans_y = getTranslate(type).second;
            brush->TranslateTransform(trans_x, trans_y);
        } else if (type.find("rotate") != std::string::npos) {
            // Apply rotation transformation
            float degree = getRotate(type);
            brush->RotateTransform(degree);
        } else if (type.find("scale") != std::string::npos) {
            // Apply scaling transformation
            if (type.find(",") != std::string::npos) {
                float scale_x = getScaleXY(type).first,
                      scale_y = getScaleXY(type).second;
                brush->ScaleTransform(scale_x, scale_y);
            } else {
                float scale = getScale(type);
                brush->ScaleTransform(scale, scale);
            }
        } else if (type.find("matrix") != std::string::npos) {
            // Apply matrix transformation
            float a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
            if (type.find(",") != std::string::npos) {
                type.erase(std::remove(type.begin(), type.end(), ','),
                           type.end());
            }
            sscanf_s(type.c_str(), "matrix(%f %f %f %f %f %f)", &a, &b, &c, &d,
                   &e, &f);
            Gdiplus::Matrix matrix(a, b, c, d, e, f);
            brush->SetTransform(&matrix);
        }
    }
}

// Apply transformation matrix operations on a path gradient brush
void Renderer::applyTransformsOnBrush(
    std::vector< std::string > transform_order,
    Gdiplus::PathGradientBrush*& brush) const {
    for (auto type : transform_order) {
        if (type.find("translate") != std::string::npos) {
            float trans_x = getTranslate(type).first,
                  trans_y = getTranslate(type).second;
            brush->TranslateTransform(trans_x, trans_y);
        } else if (type.find("rotate") != std::string::npos) {
            float degree = getRotate(type);
            brush->RotateTransform(degree);
        } else if (type.find("scale") != std::string::npos) {
            if (type.find(",") != std::string::npos) {
                float scale_x = getScaleXY(type).first,
                      scale_y = getScaleXY(type).second;
                brush->ScaleTransform(scale_x, scale_y);
            } else {
                float scale = getScale(type);
                brush->ScaleTransform(scale, scale);
            }
        } else if (type.find("matrix") != std::string::npos) {
            float a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
            if (type.find(",") != std::string::npos) {
                type.erase(std::remove(type.begin(), type.end(), ','),
                           type.end());
            }
            sscanf_s(type.c_str(), "matrix(%f %f %f %f %f %f)", &a, &b, &c, &d,
                   &e, &f);
            Gdiplus::Matrix matrix(a, b, c, d, e, f);
            brush->SetTransform(&matrix);
        }
    }
}