#include "stdafx.h"
#include "ColorShape.h"
#include <algorithm>
using namespace Gdiplus;

// const ColorShape ColorShape::Black(Color(255, 0, 0, 0));
// const ColorShape ColorShape::White(Color(255, 255, 255, 255));
// const ColorShape ColorShape::Red(Color(255, 255, 0, 0));
// const ColorShape ColorShape::Green(Color(255, 0, 255, 0));
// const ColorShape ColorShape::Blue(Color(255, 0, 0, 255));
// const ColorShape ColorShape::Yellow(Color(255, 255, 255, 0));
// const ColorShape ColorShape::Magenta(Color(255, 255, 0, 255));
// const ColorShape ColorShape::Cyan(Color(255, 0, 255, 255));
// const ColorShape ColorShape::Transparent(Color(0, 0, 0, 0));

const ColorShape ColorShape::Black(0, 0, 0);
const ColorShape ColorShape::White(255, 255, 255);
const ColorShape ColorShape::Red(255, 0, 0);
const ColorShape ColorShape::Green(0, 255, 0);
const ColorShape ColorShape::Blue(0, 0, 255);
const ColorShape ColorShape::Yellow(255, 255, 0);
const ColorShape ColorShape::Magenta(255, 0, 255);
const ColorShape ColorShape::Cyan(0, 255, 255);
const ColorShape ColorShape::Transparent(0, 0, 0, 0);

// ColorShape::ColorShape() : color(255, 0, 0, 0) {}

// ColorShape::ColorShape(BYTE red, BYTE green, BYTE blue, BYTE alpha)
// 	: color(alpha, red, green, blue) {
// }

// ColorShape::ColorShape(const Color& c) : color(c) {}

// BYTE ColorShape::getR() const { return color.GetRed(); }
// BYTE ColorShape::getG() const { return color.GetGreen(); }
// BYTE ColorShape::getB() const { return color.GetBlue(); }
// BYTE ColorShape::getA() const { return color.GetAlpha(); }

// Color ColorShape::toGDIColor() const { return color; }

// std::ostream& operator<<(std::ostream& os, const ColorShape& color)
// {
// 	os << "Color(" << static_cast<int>(color.getR()) << ", "
// 		<< static_cast<int>(color.getG()) << ", "
// 		<< static_cast<int>(color.getB()) << ", "
// 		<< static_cast<int>(color.getA()) << ")";
// 	return os;
// }

ColorShape::ColorShape() : r(0), g(0), b(0), a(255) {}

ColorShape::ColorShape(int red, int green, int blue, int alpha)
    : r(red), g(green), b(blue), a(alpha) {
    r = std::clamp(r, 0, 255);
    g = std::clamp(g, 0, 255);
    b = std::clamp(b, 0, 255);
    a = std::clamp(a, 0, 255);
}

ColorShape::ColorShape(int color)
    : r(static_cast< int >((color & 0xff000000) >> 24)),
      g(static_cast< int >((color & 0x00ff0000) >> 16)),
      b((color & 0x0000ff00) >> 8), a((color & 0x000000ff) >> 0) {}

std::ostream& operator<<(std::ostream& os, const ColorShape& color) {
    os << "Color(" << color.r << ", " << color.g << ", " << color.b << ", "
       << color.a << ")";
    return os;
}
