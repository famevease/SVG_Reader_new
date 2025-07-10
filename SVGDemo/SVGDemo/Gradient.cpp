#include "stdafx.h"

#include "Gradient.h"
Gradient::Gradient(const std::vector< Stop >& stops,
                   const std::pair< Vector2Df, Vector2Df >& points,
                   const std::string& units)
    : stops(stops), points(points), units(units) {}

std::vector< Stop > Gradient::getStops() const { return stops; }

std::pair< Vector2Df, Vector2Df > Gradient::getPoints() const { return points; }

void Gradient::setUnits(const std::string& units) { this->units = units; }

std::string Gradient::getUnits() const { return units; }

void Gradient::setTransforms(const std::vector< std::string >& transforms) {
    this->transforms = transforms;
}

std::vector< std::string > Gradient::getTransforms() const {
    return transforms;
}

void Gradient::addStop(Stop stop) { stops.push_back(stop); }