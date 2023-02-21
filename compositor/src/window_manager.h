#ifndef REVYV_WINDOWMANAGER_H
#define REVYV_WINDOWMANAGER_H

#include "window.h"
#include <compositor/types.h>
#include <iostream>

namespace revyv {
class Window;

class WindowManager {
public:
    WindowManager();

    bool send_event(const std::shared_ptr<Event>& event);

private:
    bool send_mouse_move_event(const std::shared_ptr<MouseMoveEvent>& event);

    bool send_mouse_button_event(const std::shared_ptr<MouseButtonEvent>& event);

    bool send_mouse_scroll_event(const std::shared_ptr<MouseScrollEvent>& event);

    bool send_text_event(const std::shared_ptr<TextEvent>& event);

    bool send_key_event(const std::shared_ptr<KeyEvent>& event);

private:
    std::weak_ptr<Window> _active_window;
};
}

#endif
