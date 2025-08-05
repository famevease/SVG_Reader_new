#ifndef BRUSHUTILS_H
#define BRUSHUTILS_H

#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include <algorithm>
#include "TransformUtils.h"
#include "../SVGElement.h"
#include "../graphics/RadialGradient.h"


class BrushUtils {
public:
    /**
     * @brief Utility function to apply a series of transformations to the brush
     * object.
     *
     * @param transform_order The order in which transformations should be
     * applied.
     * @param brush The Gdiplus::LinearGradientBrush object for the shape fill.
     */
    void applyTransformsOnLinearBrush(std::vector<std::string> transform_order, 
                                Gdiplus::LinearGradientBrush*& brush) const;

    /**
     * @brief Utility function to apply a series of transformations to the brush
     * object.
     *
     * @param transform_order The order in which transformations should be
     * applied.
     * @param brush The Gdiplus::PathGradientBrush object for the shape fill.
     *
     */
    void applyTransformsOnRadialBrush(std::vector<std::string> transform_order,
                                 Gdiplus::PathGradientBrush*& brush) const;

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
