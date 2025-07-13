#ifndef COLOR_SHAPE_H
#define COLOR_SHAPE_H

#include <gdiplus.h>
#include <iostream>
#include <map>
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
	ColorShape(BYTE r, BYTE g, BYTE b, BYTE a = 255);
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
/**
 * @brief A static map of named colors (CSS/SVG style names)
 */
static const std::map<std::string, ColorShape> color_map = {
	{"aliceblue", ColorShape(240, 248, 255)},
	{"antiquewhite", ColorShape(250, 235, 215)},
	{"aqua", ColorShape(0, 255, 255)},
	{"aquamarine", ColorShape(127, 255, 212)},
	{"azure", ColorShape(240, 255, 255)},
	{"beige", ColorShape(245, 245, 220)},
	{"bisque", ColorShape(255, 228, 196)},
	{"black", ColorShape(0, 0, 0)},
	{"blue", ColorShape(0, 0, 255)},
	{"blueviolet", ColorShape(138, 43, 226)},
	{"brown", ColorShape(165, 42, 42)},
	{"chocolate", ColorShape(210, 105, 30)},
	{"coral", ColorShape(255, 127, 80)},
	{"crimson", ColorShape(220, 20, 60)},
	{"cyan", ColorShape(0, 255, 255)},
	{"darkblue", ColorShape(0, 0, 139)},
	{"darkcyan", ColorShape(0, 139, 139)},
	{"darkgray", ColorShape(169, 169, 169)},
	{"darkgreen", ColorShape(0, 100, 0)},
	{"darkmagenta", ColorShape(139, 0, 139)},
	{"darkorange", ColorShape(255, 140, 0)},
	{"darkred", ColorShape(139, 0, 0)},
	{"deeppink", ColorShape(255, 20, 147)},
	{"deepskyblue", ColorShape(0, 191, 255)},
	{"dodgerblue", ColorShape(30, 144, 255)},
	{"firebrick", ColorShape(178, 34, 34)},
	{"forestgreen", ColorShape(34, 139, 34)},
	{"fuchsia", ColorShape(255, 0, 255)},
	{"gold", ColorShape(255, 215, 0)},
	{"goldenrod", ColorShape(218, 165, 32)},
	{"gray", ColorShape(128, 128, 128)},
	{"green", ColorShape(0, 128, 0)},
	{"greenyellow", ColorShape(173, 255, 47)},
	{"hotpink", ColorShape(255, 105, 180)},
	{"indigo", ColorShape(75, 0, 130)},
	{"ivory", ColorShape(255, 255, 240)},
	{"khaki", ColorShape(240, 230, 140)},
	{"lavender", ColorShape(230, 230, 250)},
	{"lawngreen", ColorShape(124, 252, 0)},
	{"lightblue", ColorShape(173, 216, 230)},
	{"lightcyan", ColorShape(224, 255, 255)},
	{"lightgreen", ColorShape(144, 238, 144)},
	{"lightpink", ColorShape(255, 182, 193)},
	{"lightsalmon", ColorShape(255, 160, 122)},
	{"lightseagreen", ColorShape(32, 178, 170)},
	{"lightskyblue", ColorShape(135, 206, 250)},
	{"lime", ColorShape(0, 255, 0)},
	{"limegreen", ColorShape(50, 205, 50)},
	{"linen", ColorShape(250, 240, 230)},
	{"magenta", ColorShape(255, 0, 255)},
	{"maroon", ColorShape(128, 0, 0)},
	{"mediumblue", ColorShape(0, 0, 205)},
	{"mediumorchid", ColorShape(186, 85, 211)},
	{"mediumpurple", ColorShape(147, 112, 219)},
	{"mediumseagreen", ColorShape(60, 179, 113)},
	{"mediumslateblue", ColorShape(123, 104, 238)},
	{"mediumspringgreen", ColorShape(0, 250, 154)},
	{"mediumturquoise", ColorShape(72, 209, 204)},
	{"midnightblue", ColorShape(25, 25, 112)},
	{"mintcream", ColorShape(245, 255, 250)},
	{"mistyrose", ColorShape(255, 228, 225)},
	{"moccasin", ColorShape(255, 228, 181)},
	{"navajowhite", ColorShape(255, 222, 173)},
	{"navy", ColorShape(0, 0, 128)},
	{"olive", ColorShape(128, 128, 0)},
	{"olivedrab", ColorShape(107, 142, 35)},
	{"orange", ColorShape(255, 165, 0)},
	{"orangered", ColorShape(255, 69, 0)},
	{"orchid", ColorShape(218, 112, 214)},
	{"palegoldenrod", ColorShape(238, 232, 170)},
	{"palegreen", ColorShape(152, 251, 152)},
	{"paleturquoise", ColorShape(175, 238, 238)},
	{"pink", ColorShape(255, 192, 203)},
	{"plum", ColorShape(221, 160, 221)},
	{"powderblue", ColorShape(176, 224, 230)},
	{"purple", ColorShape(128, 0, 128)},
	{"red", ColorShape(255, 0, 0)},
	{"rosybrown", ColorShape(188, 143, 143)},
	{"royalblue", ColorShape(65, 105, 225)},
	{"salmon", ColorShape(250, 128, 114)},
	{"sandybrown", ColorShape(244, 164, 96)},
	{"seagreen", ColorShape(46, 139, 87)},
	{"silver", ColorShape(192, 192, 192)},
	{"skyblue", ColorShape(135, 206, 235)},
	{"slateblue", ColorShape(106, 90, 205)},
	{"slategray", ColorShape(112, 128, 144)},
	{"snow", ColorShape(255, 250, 250)},
	{"springgreen", ColorShape(0, 255, 127)},
	{"steelblue", ColorShape(70, 130, 180)},
	{"tan", ColorShape(210, 180, 140)},
	{"teal", ColorShape(0, 128, 128)},
	{"thistle", ColorShape(216, 191, 216)},
	{"tomato", ColorShape(255, 99, 71)},
	{"turquoise", ColorShape(64, 224, 208)},
	{"violet", ColorShape(238, 130, 238)},
	{"wheat", ColorShape(245, 222, 179)},
	{"white", ColorShape(255, 255, 255)},
	{"yellow", ColorShape(255, 255, 0)},
	{"yellowgreen", ColorShape(154, 205, 50)}};

#endif // COLOR_SHAPE_H
