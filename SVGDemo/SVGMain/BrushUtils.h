#ifndef BRUSHUTILS_H
#define BRUSHUTILS_H

#include <gdiplus.h>
#include <vector>
#include <string>

#include "SVGElement.h"
#include "TransformUtils.h"
#include "LinearGradient.h"
#include "RadialGradient.h"

class BrushUtils {
private:
    /**
     * @brief Utility function to apply a series of transformations to the brush
     * object.
     *
     * @param transform_order The order in which transformations should be
     * applied.
     * @param brush The Gdiplus::LinearGradientBrush object for the shape fill.
     */
    static void applyTransformsOnLinearBrush(const std::vector<std::string>& transform_order, 
                                Gdiplus::LinearGradientBrush*& brush);

    /**
     * @brief Utility function to apply a series of transformations to the brush
     * object.
     *
     * @param transform_order The order in which transformations should be
     * applied.
     * @param brush The Gdiplus::PathGradientBrush object for the shape fill.
     *
     */
    static void applyTransformsOnRadialBrush(const std::vector<std::string>& transform_order,
                                 Gdiplus::PathGradientBrush*& brush);

    /**
     * @brief Gets the Gdiplus::brush object for the shape fill.
     *
     * @param shape The SVGElement representing the shape.
     * @param bound The bounding box of the shape.
     * @return The Gdiplus::brush object for the shape fill.
     */
    Gdiplus::Brush* getBrush(SVGElement* shape, Gdiplus::RectF bound) const;

};

#endif
