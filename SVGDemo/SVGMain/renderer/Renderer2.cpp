#include "Renderer2.hpp"

#include <algorithm>
#include <codecvt>
#include <locale>

#include "../SVGElement.h"
#include "DrawShape.h"
#include "../renderer/TransformUtils.h"

Renderer* Renderer::instance = nullptr;

Renderer::Renderer() {}

Renderer* Renderer::getInstance() {
    /*if (instance == nullptr) {
        instance = new Renderer();
    }
    return instance;*/

    static Renderer instance;
    return &instance;
}

void Renderer::draw(Gdiplus::Graphics& graphics, Group* group) const {
    DrawShape drawShape;

    for (auto shape : group->getElements()) {
        Gdiplus::Matrix original;
        graphics.GetTransform(&original);

        TransformUtils::applyTransform(shape->getTransforms(), graphics);

        if (shape->getClass() == "Group") {
            Group* g = dynamic_cast<Group*>(shape);
            draw(graphics, g); // Đệ quy với group con
        }
        else {
            drawShape.draw(graphics, shape); // Giao cho DrawShape xử lý
        }

        graphics.SetTransform(&original); // Khôi phục lại transform
    }
}

