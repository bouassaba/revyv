#ifndef REVYV_LISTENER_H
#define REVYV_LISTENER_H

#include <compositor/types.h>
#include <memory>
#include <thread>
#include <zmq.hpp>

namespace revyv {

class Listener {
public:
    explicit Listener(pid_t pid);

    void shutdown();

    [[nodiscard]] bool is_running() const;

private:
    void process_message(const ListenerPayload& p);

    void window_create(const ListenerPayload& p);

    void window_update_pixels(const ListenerPayload& p);

    void window_resize(const ListenerPayload& p);

    void window_set_visibility(const ListenerPayload& p);

    void window_move(const ListenerPayload& p);

    void window_bring_to_front(const ListenerPayload& p);

    void window_destroy(const ListenerPayload& p);

private:
    static void listener_thread(Listener* listener);

private:
    std::string _url;
    pid_t _pid;
    std::shared_ptr<zmq::context_t> _ctx;
    std::shared_ptr<zmq::socket_t> _socket;
    std::shared_ptr<std::thread> _thread;
    bool _running = true;
};

}

#endif
