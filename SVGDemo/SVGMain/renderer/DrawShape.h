#ifndef DRAWSHAPE_H
#define DRAWSHAPE_H

#include <gdiplus.h>
#include "Graphics.hpp"
#include "BrushUtils.h"

class DrawShape {
private:
    /**
     * @brief Draws a line shape using Gdiplus::Graphics.
     *
     * @param graphics The Gdiplus::Graphics context for drawing.
     * @param line The Line object representing the line to be drawn.
     */
    void drawLine(Gdiplus::Graphics& graphics, Line* line) const;
    
    /**
     * @brief Draws a rectangle shape using Gdiplus::Graphics.
     *
     * @param graphics The Gdiplus::Graphics context for drawing.
     * @param rectangle The Rect object representing the rectangle to be drawn.
     */
    void drawRectangle(Gdiplus::Graphics& graphics, MyRectangle* rectangle) const;

    /**
     * @brief Draws a circle shape using Gdiplus::Graphics.
     *
     * @param graphics The Gdiplus::Graphics context for drawing.
     * @param circle The Circle object representing the circle to be drawn.
     */
    void drawCircle(Gdiplus::Graphics& graphics, Circle* circle) const;

    /**
     * @brief Draws an ellipse shape using Gdiplus::Graphics.
     *
     * @param graphics The Gdiplus::Graphics context for drawing.
     * @param ellipse The Ell object representing the ellipse to be drawn.
     */
    void drawEllipse(Gdiplus::Graphics& graphics, MyEllipse* ellipse) const;
    
    /**
     * @brief Draws a polygon shape using Gdiplus::Graphics.
     *
     * @param graphics The Gdiplus::Graphics context for drawing.
     * @param polygon The Plygon object representing the polygon to be drawn.
     */
    void drawPolygon(Gdiplus::Graphics& graphics, MyPolygon* polygon) const;

    /**
     * @brief Draws a polyline shape using Gdiplus::Graphics.
     *
     * @param graphics The Gdiplus::Graphics context for drawing.
     * @param polyline The Plyline object representing the polyline to be drawn.
     */
    void drawPolyline(Gdiplus::Graphics& graphics, MyPolyLine* polyline) const;

    /**
     * @brief Draws a path shape using Gdiplus::Graphics.
     *
     * @param graphics The Gdiplus::Graphics context for drawing.
     * @param path The Path object representing the path to be drawn.
     */
    void drawPath(Gdiplus::Graphics& graphics, Path* path) const;

    /**
     * @brief Draws text using Gdiplus::Graphics.
     *
     * @param graphics The Gdiplus::Graphics context for drawing.
     * @param text The Text object representing the text to be drawn.
     */
    void drawText(Gdiplus::Graphics& graphics, Text* text) const;
};

#endif
