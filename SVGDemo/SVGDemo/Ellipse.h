#pragma once

#include "SVGElement.h"

/**
 * @brief Represents an ellipse in 2D space.
 *
 * The Ellipse class is derived from the SVGElement class and defines an ellipse
 * with a variable radius in the x and y directions.
 */

class Ellipse : public SVGElement
{
private:
    Vector2Df radius;  ///< Radius of the ellipse in the x and y directions

public:
    /**
     * @brief Constructs an Ellipse object.
     *
     * @param radius The radius of the ellipse in the x and y directions.
     * @param center The center of the ellipse.
     * @param fill Fill color of the ellipse.
     * @param stroke Outline color of the ellipse.
     * @param stroke_width Thickness of the ellipse outline.
     */
    Ellipse(const Vector2Df& radius, const Vector2Df& center, ColorShape fill, ColorShape stroke, float stroke_width);

    /**
     * @brief Gets the type of the shape.
     *
     * @return The string "Ellipse".
     *
     * @note This function is used for determining the type of the shape.
     */
    std::string getShape() const override;

    /**
     * @brief Sets the radius of the ellipse.
     *
     * @param radius The new radius of the ellipse.
     */
    void setRadius(const Vector2Df& radius);

    /**
     * @brief Gets the radius of the ellipse.
     *
     * @return The radius of the ellipse.
     */
    Vector2Df getRadius() const;

    /**
     * @brief Gets the minimum bounding box of the shape.
     *
     * @return The minimum bounding box of the shape.
     */
    Vector2Df getMinBound() const override;

    /**
     * @brief Gets the maximum bounding box of the shape.
     *
     * @return The maximum bounding box of the shape.
     */
    Vector2Df getMaxBound() const override;

    /**
     * @brief Prints the data of the shape.
     *
     * @note This function is used for debugging purposes.
     */
    //void printData() const override;
};

