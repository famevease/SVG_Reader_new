#include <windows.h>    //for func utf8_to_wstring
#include <string>       //for func utf8_to_wstring

#include "DrawShape.h"
#include "BrushUtils.h"

// Draw a line on the given graphics context
void DrawShape::drawLine(Gdiplus::Graphics& graphics, Line* line) const {
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
void DrawShape::drawRectangle(Gdiplus::Graphics& graphics,
                             MyRectangle* rectangle) const {
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
void DrawShape::drawCircle(Gdiplus::Graphics& graphics, Circle* circle) const {
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
void DrawShape::drawEllipse(Gdiplus::Graphics& graphics, MyEllipse* ellipse) const {
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

// Draw a polygon on the given graphics context
void DrawShape::drawPolygon(Gdiplus::Graphics& graphics, MyPolygon* polygon) const {
    ColorShape outline_color = polygon->getOutlineColor();
    Gdiplus::Pen polygon_outline(outline_color.toGDIColor(), polygon->getOutlineThickness());

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
    BrushUtils brush_utils;
    Gdiplus::Brush* polygon_fill = brush_utils.getBrush(polygon, bound);

    // If the fill brush is a gradient, fill the polygon with a corner color
    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(polygon_fill)) {
        ColorShape color = polygon->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(color.toGDIColor());
        graphics.FillPolygon(&corner_fill, points, idx, fill_mode);
    }

    graphics.FillPolygon(polygon_fill, points, idx, fill_mode);
    graphics.DrawPolygon(&polygon_outline, points, idx);

    delete[] points;
    delete polygon_fill;
}

// Draw a polyline on the given graphics context
void DrawShape::drawPolyline(Gdiplus::Graphics& graphics,
                            MyPolyLine* polyline) const {
    ColorShape outline_color = polyline->getOutlineColor();
    Gdiplus::Pen polyline_outline(outline_color.toGDIColor(), polyline->getOutlineThickness());

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
    BrushUtils brush_utils;
    Gdiplus::Brush* polyline_fill = brush_utils.getBrush(polyline, bound);

    // If the fill brush is a gradient, fill the polyline with a corner color
    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(polyline_fill)) {
        ColorShape color =
            polyline->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(color.toGDIColor());
        graphics.FillPath(&corner_fill, &path);
    }

    graphics.FillPath(polyline_fill, &path);
    graphics.DrawPath(&polyline_outline, &path);

    delete polyline_fill;
}

// Draw a path on the given graphics context
void DrawShape::drawPath(Gdiplus::Graphics& graphics, Path* path) const {
    ColorShape outline_color = path->getOutlineColor();
    Gdiplus::Pen path_outline(outline_color.toGDIColor(), path->getOutlineThickness());

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
                /*
                If the previous point is a quadratic bezier or a smooth quadratic bezier,
                calculate the reflection control point using the reflection formula
                */
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
    BrushUtils brush_utils;
    Gdiplus::Brush* path_fill = brush_utils.getBrush(path, bound);
    Gdiplus::Region region(&gdi_path);

    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(path_fill)) {
        ColorShape color = path->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(Gdiplus::Color(color.toGDIColor()));

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

/*
* It converts a UTF-8 encoded std::string to a UTF-16 std::wstring.
* This is necessary because Windows APIs and GDI+ use wide strings (wchar_t / UTF-16) — they don’t accept UTF-8 directly.
*/
std::wstring utf8_to_wstring(const std::string& str) {
    if (str.empty()) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// Draw text on the given graphics context
void DrawShape::drawText(Gdiplus::Graphics& graphics, Text* text) const {
    ColorShape outline_color = text->getOutlineColor();
    graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);

    Gdiplus::Pen text_outline(Gdiplus::Color(outline_color.toGDIColor()), text->getOutlineThickness());

    // Set the font family for the text
    Gdiplus::FontFamily font_family(L"Times New Roman");

    // Set the position for the text
    Gdiplus::PointF position(text->getPosition().x, text->getPosition().y);
    Gdiplus::GraphicsPath path;

    // Convert the content to wide string for GDI+
    std::wstring wide_content = utf8_to_wstring(text->getContent());

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
    BrushUtils brush_utils;
    Gdiplus::Brush* text_fill = brush_utils.getBrush(text, bound);

    // If the fill brush is a gradient, fill the text with a corner color
    if (Gdiplus::PathGradientBrush* brush =
            dynamic_cast< Gdiplus::PathGradientBrush* >(text_fill)) {
        ColorShape color = text->getGradient()->getStops().back().getColor();
        Gdiplus::SolidBrush corner_fill(Gdiplus::Color(color.toGDIColor()));
        graphics.FillPath(&corner_fill, &path);
    }

    graphics.FillPath(text_fill, &path);
    if (text->getOutlineColor().getA() != 0 &&
        text->getOutlineColor().getA() == text->getFillColor().getA()) {
        text_outline.SetColor(Gdiplus::Color(255, 255, 255, 255));
        graphics.DrawPath(&text_outline, &path);
        text_outline.SetColor(Gdiplus::Color(outline_color.toGDIColor()));
    }
    graphics.DrawPath(&text_outline, &path);

    delete text_fill;
}