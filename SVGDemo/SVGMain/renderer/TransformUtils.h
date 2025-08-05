#ifndef TRANSFORMUTILS_H
#define TRANSFORMUTILS_H

#include <windows.h>         // Quan tr?ng
#include <objidl.h>          // N?u dùng IStream
#include <gdiplus.h>         // GDI+
#pragma comment(lib, "Gdiplus.lib") // Link th? vi?n

#include <string>
#include <vector>
#include <utility>
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
