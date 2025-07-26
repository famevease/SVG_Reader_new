#include "TransformUtils.h"
#include <cstdio>

// Function to extract translation values from a transform string
std::pair<float, float> TransformUtils::getTranslate(const std::string transform_value) {
    float trans_x = 0, trans_y = 0;
    if (transform_value.find(",") != std::string::npos) {
        sscanf_s(transform_value.c_str(), "translate(%f, %f)", &trans_x,
               &trans_y);
    } else {
        sscanf_s(transform_value.c_str(), "translate(%f %f)", &trans_x, &trans_y);
    }
    return std::pair< float, float >(trans_x, trans_y);
}


// Function to extract rotation value from a transform string
float TransformUtils::getRotate(std::string transform_value) {
    float degree = 0;
    sscanf_s(transform_value.c_str(), "rotate(%f)", &degree);
    return degree;
}

// Function to extract scale value from a transform string
float TransformUtils::getScale(std::string transform_value) {
    float scale = 0;
    sscanf_s(transform_value.c_str(), "scale(%f)", &scale);
    return scale;
}

// Function to extract X and Y scale values from a transform string
std::pair< float, float > TransformUtils::getScaleXY(std::string transform_value) {
    float scale_x = 0, scale_y = 0;
    if (transform_value.find(",") != std::string::npos)
        sscanf_s(transform_value.c_str(), "scale(%f, %f)", &scale_x, &scale_y);
    else
        sscanf_s(transform_value.c_str(), "scale(%f %f)", &scale_x, &scale_y);
    return std::pair< float, float >(scale_x, scale_y);
}

// Apply transformations based on the specified order
void TransformUtils::applyTransform(const std::vector<std::string> transform_order,
                                    Gdiplus::Graphics& graphics) {
    for (auto type : transform_order) {
        if (type.find("translate") != std::string::npos) {
            float trans_x = getTranslate(type).first,
                  trans_y = getTranslate(type).second;
            graphics.TranslateTransform(trans_x, trans_y);
        } else if (type.find("rotate") != std::string::npos) {
            float degree = getRotate(type);
            graphics.RotateTransform(degree);
        } else if (type.find("scale") != std::string::npos) {
            if (type.find(",") != std::string::npos) {
                float scale_x = getScaleXY(type).first,
                      scale_y = getScaleXY(type).second;
                graphics.ScaleTransform(scale_x, scale_y);
            } else {
                float scale = getScale(type);
                graphics.ScaleTransform(scale, scale);
            }
        }
    }
}