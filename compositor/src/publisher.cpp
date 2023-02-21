#include "publisher.h"
#include "error.h"
#include <compositor/types.h>
#include <iostream>

using namespace revyv;

Publisher::Publisher(pid_t pid)
{
    _url = "ipc:///tmp/revyv-publisher-" + std::to_string(PUBLISHER_PORT_BASE + pid);
    _ctx = std::make_shared<zmq::context_t>();
    _socket = std::make_shared<zmq::socket_t>(*_ctx, ZMQ_PUSH);
    _socket->set(zmq::sockopt::sndtimeo, 10000);
    _socket->set(zmq::sockopt::rcvtimeo, 10000);
    _socket->connect(_url);
    std::cout << "Connected to event publisher for PID" << pid << " on " << _url << std::endl;
}

void Publisher::send_mouse_move_event(const std::shared_ptr<MouseMoveEvent>& event)
{
    try {
        auto req = event->translate();
        auto result = _socket->send(zmq::message_t(&req, sizeof(PublisherPayload)), zmq::send_flags::none);
        if (!result.has_value()) {
            throw FailedToSendDataError();
        }
    } catch (std::exception& e) {
        std::cout << __func__ << ": " << e.what() << std::endl;
    }
}

void Publisher::send_mouse_button_event(const std::shared_ptr<MouseButtonEvent>& event)
{
    try {
        auto req = event->translate();
        auto result = _socket->send(zmq::message_t(&req, sizeof(PublisherPayload)), zmq::send_flags::none);
        if (!result.has_value()) {
            throw FailedToSendDataError();
        }
    } catch (std::exception& e) {
        std::cout << __func__ << ": " << e.what() << std::endl;
    }
}

void Publisher::send_mouse_scroll_event(const std::shared_ptr<MouseScrollEvent>& event)
{
    try {
        auto req = event->translate();
        auto result = _socket->send(zmq::message_t(&req, sizeof(PublisherPayload)), zmq::send_flags::none);
        if (!result.has_value()) {
            throw FailedToSendDataError();
        }
    } catch (std::exception& e) {
        std::cout << __func__ << ": " << e.what() << std::endl;
    }
}

void Publisher::send_text_event(const std::shared_ptr<TextEvent>& event)
{
    try {
        auto req = event->translate();
        auto event_result = _socket->send(zmq::message_t(&req, sizeof(PublisherPayload)), zmq::send_flags::none);
        if (!event_result.has_value()) {
            throw FailedToSendDataError();
        }
        auto text_result = _socket->send(zmq::message_t(event->get_text().c_str(), event->get_text().size()), zmq::send_flags::none);
        if (!text_result.has_value()) {
            throw FailedToSendDataError();
        }
    } catch (std::exception& e) {
        std::cout << __func__ << ": " << e.what() << std::endl;
    }
}

void Publisher::send_key_event(const std::shared_ptr<KeyEvent>& event)
{
    try {
        auto req = event->translate();
        auto result = _socket->send(zmq::message_t(&req, sizeof(PublisherPayload)), zmq::send_flags::none);
        if (!result.has_value()) {
            throw FailedToSendDataError();
        }
    } catch (std::exception& e) {
        std::cout << __func__ << ": " << e.what() << std::endl;
    }
}

Publisher::~Publisher()
{
    _socket->close();
}
