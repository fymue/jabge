#ifndef ENGINE_SRC_EVENT_WINDOWEVENT_H_
#define ENGINE_SRC_EVENT_WINDOWEVENT_H_

#include "core.h"
#include "event.h"

namespace engine {

class PUB_API WindowClosedEvent: public Event {
 public:
  EVENT_INIT(WindowClosedEvent)
};

std::ostream &operator<<(std::ostream &stream, const WindowClosedEvent &event) {
  stream << event.get_name();
  return stream;
}

class PUB_API WindowFocusedEvent: public Event {
 public:
  EVENT_INIT(WindowFocusedEvent)
};

std::ostream &operator<<(std::ostream &stream,
                         const WindowFocusedEvent &event) {
  stream << event.get_name();
  return stream;
}

class PUB_API WindowMovedEvent: public Event {
 public:
  EVENT_INIT(WindowMovedEvent)
};

std::ostream &operator<<(std::ostream &stream, const WindowMovedEvent &event) {
  stream << event.get_name();
  return stream;
}

class PUB_API WindowResizedEvent: public Event {
 private:
  float _width, _height;

 public:
  EVENT_INIT(WindowResizedEvent)

  WindowResizedEvent(float width, float height) :
    _width(width), _height(height) {}

  inline float get_width() const {
    return _width;
  }

  inline float get_height() const {
    return _height;
  }
};

std::ostream &operator<<(std::ostream &stream,
                         const WindowResizedEvent &event) {
  stream << event.get_name() << ": "
         << event.get_width() << " x " << event.get_height();
  return stream;
}

}  // namespace engine

#endif  // ENGINE_SRC_EVENT_WINDOWEVENT_H_
