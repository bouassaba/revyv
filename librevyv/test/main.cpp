#include <cairo/cairo.h>
#include <chrono>
#include <iostream>
#include <revyv/revyv.h>
#include <thread>

#define SCREEN_WIDTH 1920.0
#define SCREEN_HEIGHT 1080.0
#define WINDOW_WIDTH 800.0
#define WINDOW_HEIGHT 600.0

uint32_t create_window(void* revyv_ctx)
{
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WINDOW_WIDTH, WINDOW_HEIGHT);
    cairo_t* context = cairo_create(surface);
    cairo_set_source_rgb(context, 0.80, 0.80, 0.80);
    cairo_paint(context);
    cairo_surface_flush(surface);

    unsigned long data_size = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cairo_image_surface_get_width(surface)) * cairo_image_surface_get_height(surface);
    double new_x = SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2;
    double new_y = SCREEN_HEIGHT / 2 - WINDOW_HEIGHT / 2;
    return revyv_window_create(revyv_ctx, cairo_image_surface_get_data(surface), data_size, new_x, new_y, WINDOW_WIDTH, WINDOW_HEIGHT, RevyvWindowRasterARGB);
}

void paint(void* revyv_ctx, uint32_t window_id, double x, double y)
{
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WINDOW_WIDTH, WINDOW_HEIGHT);
    cairo_t* cairoCtx = cairo_create(surface);

    cairo_set_source_rgb(cairoCtx, 0.80, 0.80, 0.80);
    cairo_paint(cairoCtx);

    cairo_set_source_rgb(cairoCtx, 0.5, 0.5, 0.5);
    cairo_rectangle(cairoCtx, x - 150, y - 150, 300, 300);
    cairo_fill(cairoCtx);

    cairo_surface_flush(surface);

    unsigned long data_size = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cairo_image_surface_get_width(surface)) * cairo_image_surface_get_height(surface);
    revyv_window_update(revyv_ctx, window_id, cairo_image_surface_get_data(surface), data_size, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

int main(int, char*[])
{
    void* revyv_ctx = revyv_context_create();

    uint32_t window_id = create_window(revyv_ctx);

    bool moveWindow = false;

    revyv_window_move(revyv_ctx, window_id, 0, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    revyv_window_move(revyv_ctx, window_id, 100, 100);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    revyv_window_move(revyv_ctx, window_id, 200, 200);

    paint(revyv_ctx, window_id, 200, 200);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    paint(revyv_ctx, window_id, 300, 200);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    paint(revyv_ctx, window_id, 400, 200);

    while (true) {
        auto event = revyv_event_wait(revyv_ctx);
        if (event.type == RevyvEventTypeMouseButton) {
            if (event.mouse_event.button == RevyvMouseButtonTypeLeft) {
                if (event.mouse_event.button_state == RevyvMouseButtonStatePressed) {
                    std::cout << "Mouse left pressed" << std::endl;
                } else if (event.mouse_event.button_state == RevyvMouseButtonStateReleased) {
                    std::cout << "Mouse left released" << std::endl;
                }
            } else if (event.mouse_event.button == RevyvMouseButtonTypeRight) {
                if (event.mouse_event.button_state == RevyvMouseButtonStatePressed) {
                    std::cout << "Mouse right pressed" << std::endl;
                } else if (event.mouse_event.button_state == RevyvMouseButtonStateReleased) {
                    std::cout << "Mouse right released" << std::endl;
                }
            }
        } else if (event.type == RevyvEventTypeMouseMove) {
            std::cout << "Mouse move (" << event.mouse_event.x << "," << event.mouse_event.y << ") "
                      << "[" << event.mouse_event.abs_x << "," << event.mouse_event.abs_y << "]" << std::endl;
            if (moveWindow) {
                revyv_window_move(
                    revyv_ctx,
                    window_id,
                    event.mouse_event.abs_x - WINDOW_WIDTH / 2,
                    event.mouse_event.abs_y - WINDOW_HEIGHT / 2);
            } else {
                paint(revyv_ctx, window_id, event.mouse_event.x, event.mouse_event.y);
            }
        } else if (event.type == RevyvEventTypeMouseScroll) {
            std::cout << "Mouse scroll "
                      << "(" << event.mouse_event.scroll_x << "," << event.mouse_event.scroll_y << ")"
                      << std::endl;
        } else if (event.type == RevyvEventTypeText) {
            std::cout << event.text_event.text << std::flush;
        } else if (event.type == RevyvEventTypeKey) {
            if (event.key_event.scancode == REVYV_SCANCODE_RETURN && event.key_event.state == RevyvKeyStatePressed) {
                moveWindow = !moveWindow;
                std::cout << "Window move activated" << std::endl;
            }
        }
    }
}
