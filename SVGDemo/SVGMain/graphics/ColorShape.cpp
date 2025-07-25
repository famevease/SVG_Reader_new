#include "stdafx.h"
#include "ColorShape.h"
#include <algorithm>
using namespace Gdiplus;

const ColorShape ColorShape::Black(Color(255, 0, 0, 0));
const ColorShape ColorShape::White(Color(255, 255, 255, 255));
const ColorShape ColorShape::Red(Color(255, 255, 0, 0));
const ColorShape ColorShape::Green(Color(255, 0, 255, 0));
const ColorShape ColorShape::Blue(Color(255, 0, 0, 255));
const ColorShape ColorShape::Yellow(Color(255, 255, 255, 0));
const ColorShape ColorShape::Magenta(Color(255, 255, 0, 255));
const ColorShape ColorShape::Cyan(Color(255, 0, 255, 255));
const ColorShape ColorShape::Transparent(Color(0, 0, 0, 0));

ColorShape::ColorShape() : color(255, 0, 0, 0) {}

ColorShape::ColorShape(BYTE red, BYTE green, BYTE blue, BYTE alpha)
	: color(alpha, red, green, blue) {
}

ColorShape::ColorShape(const Color& c) : color(c) {}

BYTE ColorShape::getR() const { return color.GetRed(); }
BYTE ColorShape::getG() const { return color.GetGreen(); }
BYTE ColorShape::getB() const { return color.GetBlue(); }
BYTE ColorShape::getA() const { return color.GetAlpha(); }

Color ColorShape::toGDIColor() const { return color; }

std::ostream& operator<<(std::ostream& os, const ColorShape& color)
{
	os << "Color(" << static_cast<int>(color.getR()) << ", "
		<< static_cast<int>(color.getG()) << ", "
		<< static_cast<int>(color.getB()) << ", "
		<< static_cast<int>(color.getA()) << ")";
	return os;
}

