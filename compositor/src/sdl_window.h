#ifndef REVYV_SDLWINDOW_H
#define REVYV_SDLWINDOW_H

#include "geometry.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <compositor/types.h>
#include <memory>
#include <queue>

namespace revyv {
enum TaskType {
    TaskTypeCreate,
    TaskTypeUpdatePixels,
    TaskTypeResize,
    TaskTypeMove,
};

struct Task {
    TaskType type;
    std::shared_ptr<unsigned char[]> pixels;
    Point point;
    Size size;
    Rect rect;
};

class SDLWindow : public Window {
public:
    SDLWindow(pid_t pid, uint32_t id, WindowRasterType raster_type, SDL_Renderer* renderer);

    virtual ~SDLWindow();

    void perform_operations_and_draw() override;

    void move(Point point) override;

    void create(std::shared_ptr<unsigned char[]> pixels, size_t bytes, const Rect& rect) override;

    void resize(std::shared_ptr<unsigned char[]> pixels, size_t bytes, const Size& size) override;

    void update_pixels(std::shared_ptr<unsigned char[]> pixel, size_t bytes, const Rect& rect) override;

private:
    void draw();

    void do_create(const Task& task);

    void do_resize(const Task& task);

    void do_update_pixels(const Task& task);

    void do_move(const Task& task);

private:
    SDL_Texture* _texture;
    SDL_Renderer* _renderer;
    std::queue<Task> _tasks;
};
}

#endif
