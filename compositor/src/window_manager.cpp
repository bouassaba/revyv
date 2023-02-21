#include "window_manager.h"
#include "server.h"
#include "window.h"

using namespace revyv;

WindowManager::WindowManager() = default;

bool WindowManager::send_event(const std::shared_ptr<Event>& event)
{
    auto event_type = event->get_type();
    if (event_type == EventTypeKey) {
        auto keyEvent = std::dynamic_pointer_cast<KeyEvent>(event);
        return this->send_key_event(keyEvent);
    } else if (event_type == EventTypeText) {
        auto textEvent = std::dynamic_pointer_cast<TextEvent>(event);
        return this->send_text_event(textEvent);
    } else if (event_type == EventTypeMouseScroll) {
        auto mouseScrollEvent = std::dynamic_pointer_cast<MouseScrollEvent>(event);
        return this->send_mouse_scroll_event(mouseScrollEvent);
    } else if (event_type == EventTypeMouseButton) {
        auto mouseButtonEvent = std::dynamic_pointer_cast<MouseButtonEvent>(event);
        return this->send_mouse_button_event(mouseButtonEvent);
    } else if (event_type == EventTypeMouseMove) {
        auto mouseMoveEvent = std::dynamic_pointer_cast<MouseMoveEvent>(event);
        return this->send_mouse_move_event(mouseMoveEvent);
    }
    return false;
}

bool WindowManager::send_mouse_move_event(
    const std::shared_ptr<MouseMoveEvent>& event)
{
    std::weak_ptr<Window> window;
    if (!_active_window.expired() && _active_window.lock() != nullptr) {
        window = _active_window;
    } else {
        window = Server::get_shared_instance()->get_compositor()->find_window_in_location(make_point(event->get_x(), event->get_y()));
    }
    if (window.expired() || window.lock() == nullptr) {
        return false;
    }
    auto point = window.lock()->get_location_in_window(make_point(event->get_x(), event->get_y()));
    event->set_window_x(point.x);
    event->set_window_y(point.y);
    auto publisher = Server::get_shared_instance()->get_publisher(window.lock()->get_pid());
    if (publisher.expired() || publisher.lock() == nullptr) {
        return false;
    }
    publisher.lock()->send_mouse_move_event(event);
    return true;
}

bool WindowManager::send_mouse_button_event(
    const std::shared_ptr<MouseButtonEvent>& event)
{
    auto compositor = Server::get_shared_instance()->get_compositor();
    if (event->get_state() == MouseButtonStatePressed) {
        auto window = compositor->find_window_in_location(
            make_point(event->get_x(), event->get_y()));
        if (window.expired() || window.lock() == nullptr) {
            return false;
        }
        _active_window = window;
        auto top_most_window = compositor->get_top_most_window();
        if (!top_most_window.expired() && top_most_window.lock() != nullptr && top_most_window.lock()->get_id() == window.lock()->get_id()) {
            auto point = window.lock()->get_location_in_window(make_point(event->get_x(), event->get_y()));
            event->set_window_x(point.x);
            event->set_window_y(point.y);
            auto publisher = Server::get_shared_instance()->get_publisher(window.lock()->get_pid());
            if (publisher.expired() || publisher.lock() == nullptr) {
                return false;
            }
            publisher.lock()->send_mouse_button_event(event);
            return true;
        } else {
            compositor->window_bring_to_front(window.lock());
            return true;
        }
    } else if (event->get_state() == MouseButtonStateReleased) {
        std::weak_ptr<Window> window;
        if (!_active_window.expired() && _active_window.lock() != nullptr) {
            window = _active_window;
            _active_window = {};
        } else {
            window = compositor->find_window_in_location(
                make_point(event->get_x(), event->get_y()));
        }
        if (window.expired() || window.lock() == nullptr) {
            return false;
        }
        auto point = window.lock()->get_location_in_window(make_point(event->get_x(), event->get_y()));
        event->set_window_x(point.x);
        event->set_window_y(point.y);
        auto publisher = Server::get_shared_instance()->get_publisher(window.lock()->get_pid());
        if (publisher.expired() || publisher.lock() == nullptr) {
            return false;
        }
        publisher.lock()->send_mouse_button_event(event);
        return true;
    }
    return false;
}

bool WindowManager::send_mouse_scroll_event(
    const std::shared_ptr<MouseScrollEvent>& event)
{
    std::weak_ptr<Window> window;
    if (!_active_window.expired() && _active_window.lock() != nullptr) {
        window = _active_window;
    } else {
        window = Server::get_shared_instance()->get_compositor()->find_window_in_location(make_point(event->get_x(), event->get_y()));
    }
    if (window.expired() || window.lock() == nullptr) {
        return false;
    }
    auto point = window.lock()->get_location_in_window(make_point(event->get_x(), event->get_y()));
    event->set_window_x(point.x);
    event->set_window_y(point.y);
    auto publisher = Server::get_shared_instance()->get_publisher(window.lock()->get_pid());
    if (publisher.expired() || publisher.lock() == nullptr) {
        return false;
    }
    publisher.lock()->send_mouse_scroll_event(event);
    return true;
}

bool WindowManager::send_text_event(const std::shared_ptr<TextEvent>& event)
{
    auto window = Server::get_shared_instance()->get_compositor()->get_top_most_window();
    if (window.expired() || window.lock() == nullptr) {
        return false;
    }
    auto publisher = Server::get_shared_instance()->get_publisher(window.lock()->get_pid());
    if (publisher.expired() || publisher.lock() == nullptr) {
        return false;
    }
    publisher.lock()->send_text_event(event);
    return true;
}

bool WindowManager::send_key_event(const std::shared_ptr<KeyEvent>& event)
{
    auto window = Server::get_shared_instance()->get_compositor()->get_top_most_window();
    if (window.expired() || window.lock() == nullptr) {
        return false;
    }
    auto publisher = Server::get_shared_instance()->get_publisher(window.lock()->get_pid());
    if (publisher.expired() || publisher.lock() == nullptr) {
        return false;
    }
    publisher.lock()->send_key_event(event);
    return true;
}
