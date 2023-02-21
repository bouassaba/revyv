#include "compositor.h"
#include <algorithm>
#include <iostream>

using namespace revyv;

Compositor::Compositor() = default;

void Compositor::add_window(const std::shared_ptr<Window>& w)
{
    _windows[w->get_id()] = w;
    _orders.push_back(w->get_id());
}

void Compositor::remove_window_by_id(uint32_t id)
{
    _windows.erase(_windows.find(id));
    _orders.erase(
        std::remove_if(
            _orders.begin(),
            _orders.end(),
            [&id](auto value) { return value == id; }),
        _orders.end());
}

void Compositor::remove_windows_by_pid(pid_t pid)
{
    for (auto it = _windows.begin(); it != _windows.end();) {
        if (it->second != nullptr && it->second->get_pid() == pid) {
            auto id = it->second->get_id();
            it = _windows.erase(_windows.find(it->second->get_id()));
            _orders.erase(
                std::remove_if(
                    _orders.begin(),
                    _orders.end(),
                    [&id](const uint32_t& value) { return value == id; }),
                _orders.end());
        } else {
            it++;
        }
    }
}

std::weak_ptr<Window> Compositor::find_window(uint32_t id)
{
    return _windows[id];
}

std::weak_ptr<Window> Compositor::find_window_in_location(Point location)
{
    for (auto it = _orders.rbegin(); it != _orders.rend();) {
        auto window = _windows[*it];
        auto frame = window->get_frame();
        if (location.x >= frame.location.x && location.x <= frame.location.x + frame.size.width
            && location.y >= frame.location.y && location.y <= frame.location.y + frame.size.height) {
            return window;
        }
        it++;
    }
    return {};
}

void Compositor::window_bring_to_front(const std::shared_ptr<Window>& w)
{
    _orders.erase(
        std::remove_if(
            _orders.begin(),
            _orders.end(),
            [&w](const uint32_t& value) { return value == w->get_id(); }),
        _orders.end());
    _orders.push_back(w->get_id());
}

std::weak_ptr<Window> Compositor::get_top_most_window()
{
    if (_windows.empty() || _orders.empty() || _windows.find(_orders.back()) == _windows.end()) {
        return {};
    }
    return _windows[_orders.back()];
}
