#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include "include/cef_render_handler.h"

class RenderHandler : public CefRenderHandler {
public:
    explicit RenderHandler(void* revyv, double x, double y, double width, double height);

    void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;

    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) override;

private:
    void* _revyv_ctx = nullptr;
    double _x {};
    double _y {};
    double _width {};
    double _height {};
    uint32_t _window_id {};

public:
    IMPLEMENT_REFCOUNTING(RenderHandler);
};

#endif
