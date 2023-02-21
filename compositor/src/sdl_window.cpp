#include "sdl_window.h"
#include "geometry.h"
#include <iostream>

using namespace revyv;

SDLWindow::SDLWindow(pid_t pid, uint32_t id, WindowRasterType raster_type, SDL_Renderer* renderer)
    : Window(pid, id, raster_type)
    , _texture(nullptr)
    , _renderer(renderer)
{
}

void SDLWindow::move(Point point)
{
    Task task {};
    task.type = TaskTypeMove;
    task.point = point;
    _tasks.push(task);
}

void SDLWindow::create(std::shared_ptr<unsigned char[]> pixels, size_t bytes, const Rect& rect)
{
    Task task {};
    task.type = TaskTypeCreate;
    task.pixels = pixels;
    task.rect = rect;
    _tasks.push(task);
}

void SDLWindow::resize(std::shared_ptr<unsigned char[]> pixels, size_t bytes, const Size& size)
{
    Task task {};
    task.type = TaskTypeResize;
    task.pixels = pixels;
    task.size = size;
    _tasks.push(task);
}

void SDLWindow::update_pixels(std::shared_ptr<unsigned char[]> pixels, size_t bytes, const Rect& rect)
{
    Task task {};
    task.type = TaskTypeUpdatePixels;
    task.pixels = pixels;
    task.rect = rect;
    _tasks.push(task);
}

void SDLWindow::perform_operations_and_draw()
{
    if (_tasks.empty()) {
        draw();
    } else {
        auto task = _tasks.front();
        switch (task.type) {
        case TaskTypeCreate:
            do_create(task);
            break;
        case TaskTypeUpdatePixels:
            do_update_pixels(task);
            break;
        case TaskTypeResize:
            do_resize(task);
            break;
        case TaskTypeMove:
            do_move(task);
        default:
            break;
        }
        draw();
        _tasks.pop();
    }
}

void SDLWindow::do_create(const Task& task)
{
    Uint32 pixel_format = SDL_PIXELFORMAT_ARGB8888;
    if (get_raster_type() == WindowRasterRGBA) {
        pixel_format = SDL_PIXELFORMAT_RGBA8888;
    } else if (get_raster_type() == WindowRasterARGB) {
        pixel_format = SDL_PIXELFORMAT_ARGB8888;
    }
    if (_texture != nullptr) {
        SDL_DestroyTexture(_texture);
    }
    _texture = SDL_CreateTexture(_renderer, pixel_format, SDL_TEXTUREACCESS_STREAMING, (int)task.rect.size.width, (int)task.rect.size.height);
    SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(_texture, nullptr, task.pixels.get(), (int)(4 * task.rect.size.width));
    set_frame(task.rect);
}

void SDLWindow::do_resize(const Task& task)
{
    Task new_task {};
    new_task.type = TaskTypeCreate;
    new_task.pixels = task.pixels;
    new_task.rect = make_rect(get_frame().location.x, get_frame().location.y, task.size.width, task.size.height);
    this->do_create(new_task);
}

void SDLWindow::do_update_pixels(const Task& task)
{
    SDL_Rect rect;
    rect.x = (int)task.rect.location.x;
    rect.y = (int)task.rect.location.y;
    rect.w = (int)task.rect.size.width;
    rect.h = (int)task.rect.size.height;
    SDL_UpdateTexture(_texture, &rect, task.pixels.get(), 4 * rect.w);
}

void SDLWindow::do_move(const Task& task)
{
    set_location(task.point);
}

void SDLWindow::draw()
{
    SDL_Rect rect;
    rect.x = (int)get_frame().location.x;
    rect.y = (int)get_frame().location.y;
    rect.w = (int)get_frame().size.width;
    rect.h = (int)get_frame().size.height;
    SDL_RenderCopy(_renderer, _texture, nullptr, &rect);
}

SDLWindow::~SDLWindow()
{
    if (_texture != nullptr) {
        SDL_DestroyTexture(_texture);
    }
}
