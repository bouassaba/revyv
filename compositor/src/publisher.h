#ifndef REVYV_PUBLISHER_H
#define REVYV_PUBLISHER_H

#include <compositor/types.h>
#include <memory>
#include <zmq.hpp>

namespace revyv {

class Publisher {
public:
    explicit Publisher(pid_t pid);

    ~Publisher();

    void send_mouse_move_event(const std::shared_ptr<MouseMoveEvent>& event);

    void send_mouse_button_event(const std::shared_ptr<MouseButtonEvent>& event);

    void send_mouse_scroll_event(const std::shared_ptr<MouseScrollEvent>& event);

    void send_text_event(const std::shared_ptr<TextEvent>& event);

    void send_key_event(const std::shared_ptr<KeyEvent>& event);

private:
    std::string _url;
    std::shared_ptr<zmq::context_t> _ctx;
    std::shared_ptr<zmq::socket_t> _socket;
};

}

#endif
