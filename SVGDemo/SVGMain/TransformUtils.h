#ifndef TRANSFORMUTILS_H
#define TRANSFORMUTILS_H

#include <string>
#include <vector>
#include <utility>
#include <gdiplus.h>

class TransformUtils {
public:
    static std::pair<float, float> getTranslate(const std::string transform_value);
    static float getRotate(const std::string transform_value);
    static float getScale(const std::string transform_value);
    static std::pair<float, float> getScaleXY(const std::string transform_value);

    static void applyTransform(const std::vector<std::string> transform_order,
                               Gdiplus::Graphics& graphics);
};

#endif
