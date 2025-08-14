#include "BrushUtils.h"
using namespace Gdiplus;

// Apply transformation matrix operations on a linear gradient brush
void BrushUtils::applyTransformsOnLinearBrush(std::vector<std::string> transform_order, LinearGradientBrush*& brush) const {
    Matrix matrix;

    for (const auto& t : transform_order) {
        std::string type = t; // cloned

        if (type.find("translate") != std::string::npos) {
            // Apply translation transformation
            auto [tx, ty] = TransformUtils::getTranslate(type);
            matrix.Translate(tx, ty);
        } 
        else if (type.find("rotate") != std::string::npos) {
            // Apply rotation transformation
            float deg = TransformUtils::getRotate(type);
            matrix.Rotate(deg);
        } 
        else if (type.find("scale") != std::string::npos) {
            // Apply scaling transformation
            if (type.find(",") != std::string::npos) {
                auto [sx, sy] = TransformUtils::getScaleXY(type);
                matrix.Scale(sx, sy);
            } 
            else {
                float s = TransformUtils::getScale(type);
                matrix.Scale(s, s);
            }
        } 
        else if (type.find("matrix") != std::string::npos) {
            // Apply matrix transformation
            float a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
            type.erase(std::remove(type.begin(), type.end(), ','), type.end());
            if (sscanf_s(type.c_str(), "matrix(%f %f %f %f %f %f)",
                &a, &b, &c, &d, &e, &f) == 6) {
                Gdiplus::Matrix m(a, b, c, d, e, f);
                matrix.Multiply(&m);
            }
        }
    }

    brush->SetTransform(&matrix);
}

// Apply transformation matrix operations on a path gradient brush
void BrushUtils::applyTransformsOnRadialBrush(std::vector<std::string> transform_order, Gdiplus::PathGradientBrush*& brush) const {
    Gdiplus::Matrix matrix;

    for (auto type : transform_order) {
        if (type.find("translate") != std::string::npos) {
            auto [tx, ty] = TransformUtils::getTranslate(type);
            matrix.Translate(tx, ty);
        }
        else if (type.find("rotate") != std::string::npos) {
            float degree = TransformUtils::getRotate(type);
            matrix.Rotate(degree);
        }
        else if (type.find("scale") != std::string::npos) {
            if (type.find(",") != std::string::npos) {
                auto [sx, sy] = TransformUtils::getScaleXY(type);
                matrix.Scale(sx, sy);
            }
            else {
                float scale = TransformUtils::getScale(type);
                matrix.Scale(scale, scale);
            }
        }
        else if (type.find("matrix") != std::string::npos) {
            float a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
            type.erase(std::remove(type.begin(), type.end(), ','), type.end());
            if (sscanf_s(type.c_str(), "matrix(%f %f %f %f %f %f)",
                &a, &b, &c, &d, &e, &f) == 6) {
                Gdiplus::Matrix m(a, b, c, d, e, f);
                matrix.Multiply(&m);
            }
        }
    }

    brush->SetTransform(&matrix);
}

// Get the Gdiplus::Brush for rendering an SVG element (shape) with a gradient or solid color
Gdiplus::Brush* BrushUtils::getBrush(SVGElement* shape,
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
            colors[0] = stops[0].getColor().toGDIColor();
            colors[stop_size - 1] = stops[stop_size - 3].getColor().toGDIColor();

            // Reverse the order of the stops
            for (size_t i = 1; i < stop_size - 1; ++i) {
                colors[i] = stops[i - 1].getColor().toGDIColor();
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
            applyTransformsOnLinearBrush(gradient->getTransforms(), fill);

            delete[] colors;
            delete[] offsets;
            return fill;
        } 
        
        else if (gradient->getClass() == "RadialGradient") {
            // Brush radiol gradient
            RadialGradient* radial_gradient =
                dynamic_cast< RadialGradient* >(gradient);
            Vector2Df radius = radial_gradient->getRadius();

            // If the gradient is in userSpaceOnUse, the radius is the distance
            if (gradient->getUnits() == "userSpaceOnUse") {
                bound.X = points.first.x - radius.x;
                bound.Y = points.first.y - radius.y;
                bound.Width = radius.x * 2;
                bound.Height = radius.y * 2;
            }

            Gdiplus::GraphicsPath path;
            path.AddEllipse(bound);
            Gdiplus::PathGradientBrush* fill =
                new Gdiplus::PathGradientBrush(&path);

            // Set the center color
            offsets[0] = 0;
            offsets[stop_size - 1] = 1;
            colors[0] = stops[stop_size - 3].getColor().toGDIColor();
            colors[stop_size - 1] = stops[0].getColor().toGDIColor();

            // Reverse the order of the stops
            for (size_t i = 1; i < stop_size - 1; ++i) {
                colors[i] = stops[stop_size - 2 - i].getColor().toGDIColor();
                offsets[i] = 1 - stops[stop_size - 2 - i].getOffset();
            }

            fill->SetInterpolationColors(colors, offsets, stop_size);
            applyTransformsOnRadialBrush(gradient->getTransforms(), fill);

            delete[] colors;
            delete[] offsets;
            return fill;
        }

		delete[] colors;
		delete[] offsets;
    }

    else {
        ColorShape color = shape->getFillColor();
        Gdiplus::SolidBrush* fill = new Gdiplus::SolidBrush(color.toGDIColor());
        return fill;
    }

    return nullptr;
}