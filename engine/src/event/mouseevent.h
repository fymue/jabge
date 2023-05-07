#ifndef ENGINE_SRC_EVENT_MOUSEEVENT_H_
#define ENGINE_SRC_EVENT_MOUSEEVENT_H_

#include "core.h"
#include "event.h"

namespace engine {

class PUB_API MouseButtonEvent: public Event  {
 private:
  int _button_code;

 protected:
  MouseButtonEvent(int button_code) :
    _button_code(button_code) {}

 public:
  inline int get_button_code() const {
    return _button_code;
  }
};

class PUB_API MousePressedEvent: public MouseButtonEvent {
 private:
  int _repeat_count;

 public:
  EVENT_INIT(MousePressedEvent)

  MousePressedEvent(int button_code, int repeat_count):
    MouseButtonEvent(button_code), _repeat_count(repeat_count) {}
};

std::ostream &operator<<(std::ostream &stream, const MousePressedEvent &event) {
  stream << event.get_name() << ": " << event.get_button_code()
         << " (repeat: )" << event._repeat_count;
  return stream;
}

class PUB_API MouseReleasedEvent: public MouseButtonEvent {
 public:
  EVENT_INIT(MouseReleasedEvent)

  MouseReleasedEvent(int button_code):
    MouseButtonEvent(button_code) {}
};

std::ostream &operator<<(std::ostream &stream,
                         const MouseReleasedEvent &event) {
  stream << event.get_name() << ": " << event.get_button_code();
  return stream;
}

class PUB_API MouseMovedEvent: public Event {
 private:
  float _x, _y;

 public:
  EVENT_INIT(MouseMovedEvent)

  MouseMovedEvent(float x, float y):
    _x(x), _y(y) {}

  inline float get_x() const {
    return _x;
  }

  inline float get_y() const {
    return _y;
  }
};

std::ostream &operator<<(std::ostream &stream, const MouseMovedEvent &event) {
  stream << event.get_name() << ": x = "
         << event.get_x() << ", y = " << event.get_y();
  return stream;
}

class PUB_API MouseScrolledEvent: public Event {
 private:
  float _x, _y;

 public:
  EVENT_INIT(MouseScrolledEvent)

  MouseScrolledEvent(float x, float y):
    _x(x), _y(y) {}

  inline float get_x() const {
    return _x;
  }

  inline float get_y() const {
    return _y;
  }
};

std::ostream &operator<<(std::ostream &stream, const MouseMovedEvent &event) {
  stream << event.get_name() << ": x = "
         << event.get_x() << ", y = " << event.get_y();
  return stream;
}

}  // namespace engine

#endif  // ENGINE_SRC_EVENT_MOUSEEVENT_H_
