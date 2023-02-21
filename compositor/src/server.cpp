#include "server.h"
#include "error.h"
#include "sdl_compositor.h"
#include "sdl_event_source.h"
#include <csignal>
#include <lzo/lzo1x.h>

using namespace revyv;

Server* Server::_shared_instance = nullptr;

Server::Server()
{
    _context = std::make_shared<zmq::context_t>();
    _socket = std::make_shared<zmq::socket_t>(*_context, ZMQ_PULL);
    _socket->set(zmq::sockopt::sndtimeo, 10000);
    _socket->set(zmq::sockopt::rcvtimeo, 10000);
    std::string url("ipc:///tmp/revyv-compositor");
    _socket->bind(url);
    std::cout << "Listening on " << url << std::endl;
}

void Server::request_listener(Server* server)
{
    for (;;) {
        try {
            ListenerPayload p {};
            auto result = server->_socket->recv(zmq::mutable_buffer(&p, sizeof(ListenerPayload)), zmq::recv_flags::none);
            if (!result.has_value()) {
                throw FailedToReceiveDataError();
            }
            if (p.type == RequestTypeClientRegister) {
                auto pid = RegisterClientPayload(p).get_pid();
                server->_publishers[pid] = std::make_shared<Publisher>(pid);
                server->_listeners[pid] = std::make_shared<Listener>(pid);
                server->add_pid(pid);
            }
        } catch (std::exception& e) {
            std::cout << __func__ << ": " << e.what() << std::endl;
        }
    }
}

void Server::process_monitor_thread(Server* server)
{
    while (true) {
        wait(5);
        for (auto pid : server->_pids) {
            if (kill(pid, 0) == -1) {
                server->_listeners[pid]->shutdown();
                uint8_t remaining_tries = 100;
                while (server->_listeners[pid]->is_running()) {
                    if (remaining_tries == 0) {
                        break;
                    }
                    wait(5);
                    remaining_tries--;
                }
                server->remove_pid(pid);
                server->remove_publisher(pid);
                server->remove_listener(pid);
                std::cout << "Unregistered PID " << pid << std::endl;
            }
        }
    }
}

void Server::run(const Size& size)
{
    if (lzo_init() != LZO_E_OK) {
        throw std::runtime_error("lzo_init() failed");
    }
    new std::thread(Server::request_listener, this);
    new std::thread(Server::process_monitor_thread, this);
    _compositor = std::make_shared<SDLCompositor>(size);
    _input_source = std::make_shared<SDLEventSource>();
    _window_manager = std::make_shared<WindowManager>();
    while (true) {
        try {
            _compositor->compose();
            auto event = _input_source->poll_event();
            if (event == nullptr) {
                continue;
            }
            auto eventType = event->get_type();
            if (eventType == EventTypeQuit) {
                break;
            } else {
                _window_manager->send_event(event);
            }
            wait(1);
        } catch (std::exception& e) {
            std::cout << __func__ << ": " << e.what() << std::endl;
        }
    }
}

void Server::add_pid(pid_t pid)
{
    _pids.push_back(pid);
}

void Server::remove_pid(pid_t pid)
{
    _compositor->remove_windows_by_pid(pid);
    _pids.erase(
        std::remove_if(
            _pids.begin(),
            _pids.end(),
            [&pid](auto value) { return value == pid; }),
        _pids.end());
}

void Server::remove_publisher(pid_t pid)
{
    _publishers.erase(_publishers.find(pid));
}

void Server::remove_listener(pid_t pid)
{
    _listeners.erase(_listeners.find(pid));
}

std::shared_ptr<Compositor> Server::get_compositor() const { return _compositor; }

std::shared_ptr<WindowManager> Server::get_window_manager() const { return _window_manager; }

std::weak_ptr<Publisher> Server::get_publisher(pid_t pid) { return _publishers[pid]; }

void Server::wait(const long milliseconds)
{
    timespec spec {};
    spec.tv_sec = 0;
    spec.tv_nsec = milliseconds * 1000000; // 1 Millisecond = 1,000,000 Nanoseconds
    nanosleep(&spec, nullptr);
}

Server* Server::get_shared_instance()
{
    if (_shared_instance == nullptr) {
        _shared_instance = new Server;
    }
    return _shared_instance;
}
