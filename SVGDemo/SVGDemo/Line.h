#ifndef Line_h_
#define Line_h_

#include "SVGElement.h"
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
	string getShape() const override; //trả về loại shape
	void setDirection(const Vector2Df& direction); 
	Vector2Df getDirection() const;
	float getLength() const; // Trả về chiều dài
};

#endif
