#ifndef REVYV_WINDOW_H
#define REVYV_WINDOW_H

#include "geometry.h"
#include <compositor/types.h>
#include <memory>

namespace revyv {
class App;

class Compositor;

class Window {
public:
    Window(pid_t pid, uint32_t id, WindowRasterType raster_type);

    virtual ~Window();

    [[nodiscard]] uint32_t get_id() const;

    [[nodiscard]] static uint32_t new_window_id();

    [[nodiscard]] Rect get_frame() const;

    void set_frame(const Rect& frame);

    void set_location(const Point& location);

    [[nodiscard]] bool is_visible() const;

    void set_visible(bool visible);

    virtual void perform_operations_and_draw() = 0;

    virtual void move(Point point) = 0;

    virtual void create(std::shared_ptr<unsigned char[]> pixels, size_t bytes, const Rect& rect) = 0;

    virtual void resize(std::shared_ptr<unsigned char[]> pixels, size_t bytes, const Size& size) = 0;

    virtual void update_pixels(std::shared_ptr<unsigned char[]> pixels, size_t bytes, const Rect& dirty_rect) = 0;

    [[nodiscard]] pid_t get_pid() const;

    Point get_location_in_window(Point location_in_screen);

    [[nodiscard]] int get_raster_type() const;

    void set_raster_type(WindowRasterType raster_type);

    [[nodiscard]] int get_shared_memory_id() const;

    void set_shared_memory_id(int shared_memory_id);

    [[nodiscard]] unsigned char* get_shared_memory_address() const;

    void set_shared_memory_address(unsigned char* shared_memory_address);

private:
    pid_t _pid;
    uint32_t _id;
    Rect _frame;
    bool _visible;
    static uint32_t _id_counter;
    WindowRasterType _raster_type;
    int _shared_memory_id = -1;
    unsigned char* _shared_memory_address = nullptr;
};
}

#endif
