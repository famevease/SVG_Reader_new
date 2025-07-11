#ifndef COLOR_SHAPE_H
#define COLOR_SHAPE_H

#include <gdiplus.h>
#include <iostream>
#pragma comment(lib, "gdiplus.lib")

class ColorShape
{
public:
	static const ColorShape Black;
	static const ColorShape White;
	static const ColorShape Red;
	static const ColorShape Green;
	static const ColorShape Blue;
	static const ColorShape Yellow;
	static const ColorShape Magenta;
	static const ColorShape Cyan;
	static const ColorShape Transparent;

	ColorShape();
	ColorShape(BYTE red, BYTE green, BYTE blue, BYTE alpha = 255);
	ColorShape(const Gdiplus::Color &color);

	BYTE getR() const;
	BYTE getG() const;
	BYTE getB() const;
	BYTE getA() const;

	Gdiplus::Color toGDIColor() const;

	friend std::ostream &operator<<(std::ostream &os, const ColorShape &color);

private:
	Gdiplus::Color color;
};

#endif // COLOR_SHAPE_H
