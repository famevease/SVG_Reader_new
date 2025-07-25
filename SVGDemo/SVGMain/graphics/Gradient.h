#pragma once

#include "GdiHelper.h"
#include "Stop.h"
#include "Vector2D.hpp"

/**
 * @brief A class that represents a gradient.
 *
 * The Gradient class is an abstract class that represents a gradient. It
 * contains a vector of Stop objects that represent the stops of the gradient.
 * It also contains a pair of Vector2D objects that represent the start and end
 * points of the gradient.
 */
class Gradient {
private:
    std::vector< Stop > stops;  ///< Stops of the gradient
    std::pair< Vector2Df, Vector2Df >
        points;         ///< Start and end points of the gradient
    std::string units;  ///< Units of the gradient
    std::vector< std::string > transforms;  ///< Transforms of the gradient

public:
    /**
     * @brief Constructs a Gradient object.
     *
     * @param stops The stops of the gradient.
     * @param points The start and end points of the gradient.
     * @param units The units of the gradient.
     */
    Gradient(const std::vector< Stop >& stops,
             const std::pair< Vector2Df, Vector2Df >& points, 
             const std::string& units);

    /**
     * @brief Destructs a Gradient object.
     */
    virtual ~Gradient() = default;

    /**
     * @brief Gets the type of the gradient.
     *
     * @return The string that represents the type of the gradient.
     */
    virtual std::string getClass() const = 0;

    /**
     * @brief Gets the stops of the gradient.
     *
     * @return The stops of the gradient.
     */
    std::vector< Stop > getStops() const;

    /**
     * @brief Gets the start and end points of the gradient.
     *
     * @return The start and end points of the gradient.
     */
    std::pair< Vector2Df, Vector2Df > getPoints() const;

    /**
     * @brief Gets the units of the gradient.
     *
     * @return The units of the gradient.
     */
    void setUnits(const std::string& units);

    /**
     * @brief Gets the units of the gradient.
     *
     * @return The units of the gradient.
     */
    std::string getUnits() const;

    /**
     * @brief Gets the transforms of the gradient.
     *
     * @return The transforms of the gradient.
     */
    void setTransforms(const std::vector< std::string >& transforms);

    /**
     * @brief Gets the transforms of the gradient.
     *
     * @return The transforms of the gradient.
     */
    std::vector< std::string > getTransforms() const;

    /**
     * @brief Adds a stop to the gradient.
     *
     * @param stop The stop to be added to the gradient.
     */
    void addStop(Stop stop);


};