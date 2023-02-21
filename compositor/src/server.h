#ifndef REVYV_SERVER_H
#define REVYV_SERVER_H

#include "compositor.h"
#include "event_source.h"
#include "listener.h"
#include "publisher.h"
#include "window_manager.h"
#include <memory>
#include <queue>
#include <thread>
#include <vector>
#include <zmq.hpp>

namespace revyv {

class Server {
public:
    static Server* get_shared_instance();

    void run(const Size& size);

    void add_pid(pid_t pid);

    void remove_pid(pid_t pid);

    void remove_publisher(pid_t pid);

    void remove_listener(pid_t pid);

    [[nodiscard]] std::weak_ptr<Publisher> get_publisher(pid_t pid);

    [[nodiscard]] std::shared_ptr<Compositor> get_compositor() const;

    [[nodiscard]] std::shared_ptr<WindowManager> get_window_manager() const;

private:
    Server();

    static void wait(long milliseconds);

    static void request_listener(Server* server);

    static void process_monitor_thread(Server* server);

private:
    std::vector<pid_t> _pids;
    std::unordered_map<pid_t, std::shared_ptr<Listener>> _listeners;
    std::unordered_map<pid_t, std::shared_ptr<Publisher>> _publishers;
    std::shared_ptr<EventSource> _input_source = nullptr;
    std::shared_ptr<Compositor> _compositor = nullptr;
    std::shared_ptr<WindowManager> _window_manager = nullptr;
    std::shared_ptr<std::thread> _message_dispatcher;
    std::shared_ptr<zmq::context_t> _context = nullptr;
    std::shared_ptr<zmq::socket_t> _socket = nullptr;
    static Server* _shared_instance;
};
}

#endif
