#ifndef REVYV_EVENTSOURCE_H
#define REVYV_EVENTSOURCE_H

#include <compositor/types.h>
#include <iostream>
#include <memory>

namespace revyv {

class EventSource {
public:
    [[nodiscard]] virtual std::shared_ptr<Event> poll_event() = 0;
};
}

#endif
