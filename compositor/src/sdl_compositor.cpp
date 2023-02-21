#include "sdl_compositor.h"
#include <memory>

using namespace revyv;

SDLCompositor::SDLCompositor(const Size& size)
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        _window = SDL_CreateWindow("Revyv", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)size.width, (int)size.height, SDL_WINDOW_SHOWN);
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
    }
}

void SDLCompositor::compose()
{
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);
    for (auto it = _orders.begin(); it != _orders.end();) {
        if (_windows.find(*it) == _windows.end()) {
            continue;
        }
        auto window = _windows[*it];
        if (window != nullptr) {
            window->perform_operations_and_draw();
        }
        it++;
    }
    SDL_RenderPresent(_renderer);
}

SDL_Renderer* SDLCompositor::get_renderer() const
{
    return _renderer;
}

SDLCompositor::~SDLCompositor()
{
    SDL_Quit();
}
