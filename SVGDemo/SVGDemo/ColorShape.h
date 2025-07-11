#ifndef ColorShape_h_
#define ColorShape_h_

class ColorShape{
public:
	float r = 0, g = 0, b = 0, opacity = 1; // cường độ đỏ, xanh lá, xanh dương, độ trong suốt
	ColorShape() {}
	ColorShape(float r, float g, float b, float o): r(r), g(g), b(b), opacity(o){}
};

class stroke {
private:
	ColorShape strokeColor;
	float strokeWidth;
public:
	stroke();
	~stroke();

	ColorShape getStrokeColor();
	float getStrokeWidth();

	void setStrokeColor(ColorShape);
	void setStrokeWidth(float);
};

#endif