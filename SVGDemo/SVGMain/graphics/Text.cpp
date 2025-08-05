#include "Text.h"

Text::Text(Vector2Df pos, std::string text, float font_size,
    const ColorShape& fill, const ColorShape& stroke, float stroke_width)
    : SVGElement(fill, stroke, stroke_width, pos), content(text),
    font_size(font_size) {
}

std::string Text::getClass() const { return "Text"; }

void Text::setFontSize(float font_size) { this->font_size = font_size; }

float Text::getFontSize() const { return font_size; }

void Text::setContent(std::string content) { this->content = content; }

std::string Text::getContent() const { return content; }

void Text::setAnchor(std::string anchor) { this->anchor = anchor; }

std::string Text::getAnchor() const { return anchor; }

void Text::setFontStyle(std::string font_style) { this->style = font_style; }

std::string Text::getFontStyle() const { return style; }

void Text::printData() const {
   SVGElement::printData();
   std::cout << "Content: " << getContent() << std::endl;
   std::cout << "Font size: " << getFontSize() << std::endl;
}
Vector2Df Text::getMinBound() const {
    return Vector2Df(SVGElement::getPosition().x, SVGElement::getPosition().y - font_size);
}
Vector2Df Text::getMaxBound() const {
    return Vector2Df(SVGElement::getPosition().x + content.length() * font_size / 2, SVGElement::getPosition().y + font_size);
}
std::vector<std::string> Text::getTransforms() const {
    return SVGElement::getTransforms();
}
SVGElement* Text::getParent() const {
    return SVGElement::getParent();
}
void Text::addElement(SVGElement* element) {
    // Text elements do not support adding elements, so we can throw an exception or ignore
    throw std::runtime_error("Cannot add elements to a Text.");
}
// Gradient* Text::getGradient() const {
//     return SVGElement::getGradient();
// }
// void Text::setGradient(Gradient* gradient) {
//     SVGElement::setGradient(gradient);
// }
