#ifndef REVYV_SDLCOMPOSITOR_H
#define REVYV_SDLCOMPOSITOR_H

#include "compositor.h"
#include <SDL2/SDL.h>
#include <memory>

namespace revyv {
class SDLCompositor : public Compositor {
public:
    explicit SDLCompositor(const Size& size);

    virtual ~SDLCompositor();

    void compose() override;

    [[nodiscard]] SDL_Renderer* get_renderer() const;

private:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
};
}

#endif
