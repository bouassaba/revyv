#include "window.h"
#include <sys/shm.h>

using namespace revyv;

uint32_t Window::_id_counter = 0;

Window::Window(pid_t pid, uint32_t id, WindowRasterType raster_type)
    : _pid(pid)
    , _id(id)
    , _raster_type(raster_type)
    , _frame(make_rect(0, 0, 0, 0))
    , _visible(true)
{
}

Window::~Window()
{
    if (_shared_memory_address != nullptr) {
        shmdt(_shared_memory_address);
    }
}

Point Window::get_location_in_window(Point location_in_screen)
{
    return make_point(location_in_screen.x - _frame.location.x, location_in_screen.y - _frame.location.y);
}

uint32_t Window::new_window_id()
{
    return ++_id_counter;
}

uint32_t Window::get_id() const
{
    return _id;
}

Rect Window::get_frame() const
{
    return _frame;
}

void Window::set_frame(const Rect& frame)
{
    _frame = frame;
}

void Window::set_location(const Point& location)
{
    _frame.location = location;
}

bool Window::is_visible() const
{
    return _visible;
}

void Window::set_visible(bool visible)
{
    _visible = visible;
}

int Window::get_raster_type() const
{
    return _raster_type;
}

void Window::set_raster_type(WindowRasterType raster_type)
{
    _raster_type = raster_type;
}

int Window::get_shared_memory_id() const
{
    return _shared_memory_id;
}

void Window::set_shared_memory_id(int shared_memory_id)
{
    _shared_memory_id = shared_memory_id;
}

unsigned char* Window::get_shared_memory_address() const
{
    return _shared_memory_address;
}

void Window::set_shared_memory_address(unsigned char* shared_memory_address)
{
    _shared_memory_address = shared_memory_address;
}

pid_t Window::get_pid() const
{
    return _pid;
}
