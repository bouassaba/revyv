#ifndef REVYV_SDLINPUTSOURCE_H
#define REVYV_SDLINPUTSOURCE_H

#include "event_source.h"
#include <memory>

namespace revyv {
class SDLEventSource : public EventSource {
public:
    SDLEventSource();

    [[nodiscard]] std::shared_ptr<Event> poll_event() override;

private:
    double _mouse_x = 0;
    double _mouse_y = 0;
};
}

#endif
