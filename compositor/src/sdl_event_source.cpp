#include "sdl_event_source.h"
#include "server.h"
#include <SDL2/SDL.h>

using namespace revyv;

SDLEventSource::SDLEventSource() = default;

std::shared_ptr<Event> SDLEventSource::poll_event()
{
    SDL_Event sdl_event;
    if (SDL_PollEvent(&sdl_event)) {
        if (sdl_event.type == SDL_QUIT) {
            return std::make_shared<QuitEvent>();
        } else if (sdl_event.type == SDL_MOUSEMOTION) {
            _mouse_x = sdl_event.motion.x;
            _mouse_y = sdl_event.motion.y;
            auto event = std::make_shared<MouseMoveEvent>();
            event->set_timestamp(sdl_event.motion.timestamp);
            event->set_x(sdl_event.motion.x);
            event->set_y(sdl_event.motion.y);
            return event;
        } else if (sdl_event.type == SDL_MOUSEBUTTONDOWN || sdl_event.type == SDL_MOUSEBUTTONUP) {
            auto event = std::make_shared<MouseButtonEvent>();
            event->set_timestamp(sdl_event.button.timestamp);
            event->set_x(sdl_event.motion.x);
            event->set_y(sdl_event.motion.y);
            if (sdl_event.type == SDL_MOUSEBUTTONDOWN) {
                event->set_state(MouseButtonStatePressed);
            } else if (sdl_event.type == SDL_MOUSEBUTTONUP) {
                event->set_state(MouseButtonStateReleased);
            } else {
                event->set_state(MouseButtonStateUndefined);
            }
            if (sdl_event.button.button == SDL_BUTTON_RIGHT) {
                event->set_button(MouseButtonTypeRight);
            } else if (sdl_event.button.button == SDL_BUTTON_LEFT) {
                event->set_button(MouseButtonTypeLeft);
            } else if (sdl_event.button.button == SDL_BUTTON_MIDDLE) {
                event->set_button(MouseButtonTypeMiddle);
            } else {
                event->set_button(MouseButtonTypeUndefined);
            }
            event->setClicks(sdl_event.button.clicks);
            return event;
        } else if (sdl_event.type == SDL_MOUSEWHEEL) {
            auto event = std::make_shared<MouseScrollEvent>();
            event->set_timestamp(sdl_event.wheel.timestamp);
            event->set_x(_mouse_x);
            event->set_y(_mouse_y);
            event->setScrollX(sdl_event.wheel.x);
            event->setScrollY(sdl_event.wheel.y);
            event->set_flipped(false);
            return event;
        } else if (sdl_event.type == SDL_KEYDOWN || sdl_event.type == SDL_KEYUP) {
            auto event = std::make_shared<KeyEvent>();
            event->set_timestamp(sdl_event.key.timestamp);
            event->set_keycode(sdl_event.key.keysym.sym);
            event->set_keymod(sdl_event.key.keysym.mod);
            event->set_scancode(sdl_event.key.keysym.scancode);
            event->set_repeat(sdl_event.key.repeat);
            if (sdl_event.key.state == SDL_PRESSED) {
                event->set_state(KeyStatePressed);
            } else if (sdl_event.key.state == SDL_RELEASED) {
                event->set_state(KeyStateReleased);
            } else {
                event->set_state(KeyStateUndefined);
            }
            return event;
        } else if (sdl_event.type == SDL_TEXTINPUT) {
            auto event = std::make_shared<TextEvent>();
            event->set_text(sdl_event.text.text);
            return event;
        }
    }
    return nullptr;
}
