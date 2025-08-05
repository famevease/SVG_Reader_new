#ifndef Line_h_
#define Line_h_


#include "../SVGElement.h"
/*
* Lớp Line kế thừa SVGElement thể hiện một đoạn đường có hướng và độ dày xác định
*/
class Line : public SVGElement {
private:
	Vector2Df direction; //Hướng của đường, g
public:
	/*
	* Point 1: điểm đầu
	* Point 2: điểm cuối
	* stroke: màu của line
	* stroke_with: đồ dày (mặc định là 1.0)
	*/
	Line(const Vector2Df& point1, const Vector2Df& point2, ColorShape stroke, float stroke_with);
	std::string getClass() const override; //trả về loại shape
	void setDirection(const Vector2Df& direction); 
	Vector2Df getDirection() const;
	float getLength() const; // Trả về chiều dài
	Vector2Df getMinBound() const override; // Trả về bound nhỏ nhất của đường
	Vector2Df getMaxBound() const override; // Trả về bound lớn nhất của đường
	void printData() const override; // In dữ liệu của đường
	/**
	 * @brief Gets the minimum bounding box of the shape.
	 * @return The minimum bounding box of the shape.
	 */
	std::vector<std::string> getTransforms() const;
	/**
	 * @brief Gets the maximum bounding box of the shape.
	 * @return The maximum bounding box of the shape.
	 */
	SVGElement* getParent() const override; // Trả về parent của đường
	/**
	 * @brief Adds a shape to the composite group.
	 * @param element The shape to be added to the composite group.
	 */
	void addElement(SVGElement* element) override;
	/**
	 * @brief Gets the direction of the line.
	 * @return The direction of the line.
	 */



};

#endif
