#pragma once

#include "PolyShape.h"

/**
 * @brief Represents a polygon in 2D space.
 *
 * The Polygon class is derived from the PolyShape class and defines a polygon
 * with a variable number of vertices.
 */
class Polygon : public PolyShape
{
public:
    /**
     * @brief Constructs a Polygon object.
     *
     * @param fill Fill color of the polygon (default issf::Color::Transparent).
     * @param stroke Outline color of the polygon (default is sf::Color::White).
     * @param stroke_width Thickness of the polygon outline (default is 0).
     */
    Polygon(ColorShape fill, ColorShape stroke, float stroke_width);

    /**
     * @brief Gets the type of the shape.
     *
     * @return The string "Polygon".

     */
    std::string getShape() const override;
};

