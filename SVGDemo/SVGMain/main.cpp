// clang-format off
#include <winsock2.h>
#include <objidl.h>
#include <windows.h>
#include <gdiplus.h>

// clang-format on

#include "Parser.h"
#include "Viewer.hpp"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// Fix for the errors by ensuring the correct usage of `std::min`
// The issue arises because `min` might be defined as a macro in Windows headers.
// Undefine the macro to avoid conflicts.

#ifdef min
#undef min
#endif

#include <algorithm>

Parser* parser = nullptr;

void OnPaint(HDC hdc, const std::string& filePath, Viewer& viewer) {
    Gdiplus::Graphics graphics(hdc);

    // Set up the graphics object for antialiased rendering.
    if (!parser) {
        parser = Parser::getInstance(filePath);
    }

    // Set up Viewbox and Viewport
    Vector2Df viewport = parser->getViewPort();
    ViewBox viewbox = parser->getViewBox();
    if (viewport.x == 0 && viewport.y == 0) {
        viewport.x = viewer.window_size.x;
        viewport.y = viewer.window_size.y;
    }

    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
    graphics.SetTextContrast(100);
    graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
    graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
    graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

    graphics.SetClip(Gdiplus::Rect(0, 0, viewport.x, viewport.y));
    if ((viewport.x != viewbox.getWidth() ||
         viewport.y != viewbox.getHeight()) &&
        viewbox.getWidth() != 0 && viewbox.getHeight() != 0) {
        float scale_x = viewport.x / viewbox.getWidth();
        float scale_y = viewport.y / viewbox.getHeight();
        float scale = std::min(scale_x, scale_y);
        graphics.ScaleTransform(scale, scale);
        float offset_x = 0.0f;
        float offset_y = 0.0f;
        if (viewport.x > viewbox.getWidth()) {
            offset_x = (viewport.x - viewbox.getWidth() * scale) / 2 / scale;
        }
        if (viewport.y > viewbox.getHeight()) {
            offset_y = (viewport.y - viewbox.getHeight() * scale) / 2 / scale;
        }
        graphics.TranslateTransform(offset_x, offset_y);
    }
    graphics.TranslateTransform(-viewbox.getX(), -viewbox.getY());

    Gdiplus::Matrix matrix;
    Gdiplus::Region region;
    graphics.GetClip(&region);
    graphics.RotateTransform(viewer.rotate_angle);
    graphics.ScaleTransform(viewer.zoom_factor, viewer.zoom_factor);
    graphics.TranslateTransform(viewer.offset_x, viewer.offset_y);
    graphics.SetClip(&region);

    // Render the SVG file.
    Renderer* renderer = Renderer::getInstance();
    SVGElement* root = parser->getRoot();
    Group* group = dynamic_cast< Group* >(root);
    renderer->draw(graphics, group);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
    HWND hWnd;
    MSG msg;
    WNDCLASS wndClass;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("svg-reader-v0.2");

    RegisterClass(&wndClass);

    hWnd = CreateWindowEx(0,
                          TEXT("svg-reader-v0.2"),  // window class name
                          TEXT("svg-reader-v0.2"),  // window caption
                          WS_OVERLAPPEDWINDOW,      // window style
                          0,                        // initial x position
                          0,                        // initial y position
                          1600,                     // initial x size
                          900,                      // initial y size
                          NULL,                     // parent window handle
                          NULL,                     // window menu handle
                          hInstance,                // program instance handle
                          NULL);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (parser) delete parser;
    Gdiplus::GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    std::string filePath;
    if (__argc > 1) {
        filePath = __argv[1];
        std::ifstream file(filePath);
        if (!file.good()) {
            std::cerr << "Error: File path is invalid or does not exist."
                      << std::endl;
            PostQuitMessage(0);
            return 0;
        }
        file.close();
    } else {
        std::cerr << "Error: No file path provided." << std::endl;
        PostQuitMessage(0);
        return 0;
    }
    Viewer* viewer = Viewer::getInstance();
    switch (message) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            viewer->getWindowSize(hWnd);
            OnPaint(hdc, filePath, *viewer);
            EndPaint(hWnd, &ps);
            return 0;
        case WM_MOUSEWHEEL:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            viewer->handleMouseEvent(message, wParam, lParam);
            if (viewer->needs_repaint) {
                InvalidateRect(hWnd, NULL, TRUE);
                viewer->needs_repaint = false;
            }
            return 0;
        case WM_KEYDOWN:
            viewer->handleKeyEvent(wParam);
            InvalidateRect(hWnd, NULL, TRUE);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}