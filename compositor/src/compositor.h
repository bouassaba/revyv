#ifndef REVYV_COMPOSITOR_H
#define REVYV_COMPOSITOR_H

#include "geometry.h"
#include "window.h"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace revyv {
class Compositor {
public:
    Compositor();

    virtual void compose() = 0;

    void add_window(const std::shared_ptr<Window>& w);

    [[nodiscard]] std::weak_ptr<Window> find_window(uint32_t id);

    void remove_window_by_id(uint32_t id);

    void remove_windows_by_pid(pid_t pid);

    [[nodiscard]] std::weak_ptr<Window> find_window_in_location(Point location);

    void window_bring_to_front(const std::shared_ptr<Window>& w);

    [[nodiscard]] std::weak_ptr<Window> get_top_most_window();

protected:
    std::unordered_map<uint32_t, std::shared_ptr<Window>> _windows;
    std::vector<uint32_t> _orders;
};
}

#endif
