#pragma once

#include "PolyShape.h"

/**
 * @brief Represents a polyline in 2D space.
 *
 * The Polyline class is derived from the PolyShape class and defines a polyline
 * with a variable number of vertices.
 */
class PolyLine : public PolyShape
{
public:
    /**
     * @brief Constructs a Polyline object.
     *
     * @param stroke_width The stroke width of the polyline (default is 0).
     * @param stroke The stroke color of the polyline (default is sf::Color::White).
     * @param fill The fill color of the polyline (default is sf::Color::Transparent).
     */
    PolyLine(const ColorShape& fill, const ColorShape& stroke, float stroke_width);

    /**
     * @brief Gets the type of the shape.
     *
     * @return The string "Polyline".
     */
    std::string getShape() const override;
};

