#ifndef Line_h_
#define Line_h_

#include "../SVGElement.h"
/*
 * Lớp Line kế thừa SVGElement thể hiện một đoạn đường có hướng và độ dày xác định
 */
class Line : public SVGElement
{
private:
	Vector2Df direction; // Hướng của đường, g
public:
	/*
	 * Point 1: first point
	 * Point 2: last point
	 * stroke: color of line
	 * stroke_with: thickness (default 1.0)
	 */
	Line(const Vector2Df &point1, const Vector2Df &point2, ColorShape stroke, float stroke_with);
	std::string getClass() const override; // return what kind of shape
	void setDirection(const Vector2Df &direction);
	Vector2Df getDirection() const;
	float getLength() const;				// return length
	Vector2Df getMinBound() const override; // return min bound of line
	Vector2Df getMaxBound() const override; // return max bound of line
	void printData() const override;		// print data of line
	/**
	 * @brief Gets the minimum bounding box of the shape.
	 * @return The minimum bounding box of the shape.
	 */
	std::vector<std::string> getTransforms() const;
	/**
	 * @brief Gets the maximum bounding box of the shape.
	 * @return The maximum bounding box of the shape.
	 */
	SVGElement *getParent() const override; // Trả về parent của đường
	/**
	 * @brief Adds a shape to the composite group.
	 * @param element The shape to be added to the composite group.
	 */
	void addElement(SVGElement *element) override;
	/**
	 * @brief Gets the direction of the line.
	 * @return The direction of the line.
	 */
};

#endif
