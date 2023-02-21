#ifndef REVYV_SOCKET_H
#define REVYV_SOCKET_H

#include <cerrno>
#include <compositor/types.h>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <vector>
#include <zmq.hpp>

namespace revyv {

typedef enum { SocketConnect = 1,
    SocketBind = 2 } SocketMode;

class FailedToSendDataError : public std::runtime_error {
public:
    FailedToSendDataError()
        : std::runtime_error("Failed to send data")
    {
    }
};

class FailedToReceiveDataError : public std::runtime_error {
public:
    FailedToReceiveDataError()
        : std::runtime_error("Failed to receive data")
    {
    }
};

class Socket {
public:
    explicit Socket(SocketMode mode, const std::string& url)
        : _url(url)
    {
        _ctx = std::make_shared<zmq::context_t>();
        if (mode == SocketConnect) {
            _socket = std::make_shared<zmq::socket_t>(*_ctx, ZMQ_PUSH);
            _socket->connect(url);
        } else if (mode == SocketBind) {
            _socket = std::make_shared<zmq::socket_t>(*_ctx, ZMQ_PULL);
            _socket->bind(_url);
        }
    }

    ~Socket() { _socket->close(); }

    void send_listener_payload(ListenerPayload p)
    {
        auto result = _socket->send(zmq::message_t(&p, sizeof(ListenerPayload)), zmq::send_flags::none);
        if (!result.has_value()) {
            throw FailedToSendDataError();
        }
    }

    void send_data(unsigned char* data, size_t size)
    {
        auto result = _socket->send(zmq::message_t((const void*)data, (size_t)size), zmq::send_flags::none);
        if (!result.has_value()) {
            throw FailedToSendDataError();
        }
    }

    PublisherPayload recv_publisher_payload()
    {
        PublisherPayload p {};
        auto result = _socket->recv(zmq::mutable_buffer(&p, sizeof(PublisherPayload)), zmq::recv_flags::none);
        if (!result.has_value()) {
            throw FailedToReceiveDataError();
        }
        return p;
    }

    std::shared_ptr<char[]> recv_rext(size_t length)
    {
        std::shared_ptr<char[]> text(new char[length]);
        auto result = _socket->recv(zmq::mutable_buffer(text.get(), (size_t)(length - 1)), zmq::recv_flags::none);
        if (!result.has_value()) {
            return nullptr;
        }
        text[(int)(length - 1)] = 0;
        return text;
    }

    [[nodiscard]] const std::string& get_url() const { return _url; }

private:
    std::string _url;
    std::shared_ptr<zmq::context_t> _ctx;
    std::shared_ptr<zmq::socket_t> _socket;
};
}

#endif
