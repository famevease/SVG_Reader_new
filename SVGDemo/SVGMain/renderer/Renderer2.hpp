#ifndef RENDERER2_HPP_
#define RENDERER2_HPP_
// clang-format off
#include <winsock2.h>
#include <objidl.h>
#include <windows.h>
#include <wingdi.h>
#include <gdiplus.h>

// clang-format on
#include "../Graphics.hpp"
 #include "../SVGElement.h"
 #include "DrawShape.h"
 #include "TransformUtils.h"

/**
 * @brief Singleton class responsible for rendering shapes using GDI+.
 *
 * The Renderer class provides a singleton instance for drawing SVGElement-based
 * shapes using Gdiplus::Graphics. It supports various shapes such as lines,
 * rectangles, circles, ellipses, text, polygons, polylines, and paths. The
 * shapes are drawn in a polymorphic manner using the draw function, which takes
 * a Gdiplus::Graphics context and an SVGElement. The draw function dynamically
 * determines the type of the shape and invokes the corresponding draw method to
 * render the shape with all necessary details. The detailed information for
 * each shape is obtained from an SVG file and processed through the draw
 * function in a polymorphic way.
 */
class Renderer {
public:
    /**
     * @brief Gets the singleton instance of the Renderer class.
     *
     * @return The singleton instance of the Renderer class.
     */
    static Renderer* getInstance();

    /**
     * @brief Deleted copy constructor to enforce the singleton pattern.
     */
    Renderer(const Renderer&) = delete;

    /**
     * @brief Deleted copy assignment operator to enforce the singleton pattern.
     */
    void operator=(const Renderer&) = delete;

    /**
    * @brief Draws a shape using Gdiplus::Graphics based on its type.
    *
    * @param graphics The Gdiplus::Graphics context for drawing.
    * @param shape The SVGElement representing the shape to be drawn.
    */
    void draw(Gdiplus::Graphics& graphics, Group* group) const;

private:
    /**
     * @brief Private constructor for the Renderer class.
     */
    Renderer();

    static Renderer* instance;  ///< Singleton instance of the Renderer class
};

#endif