#ifndef ENGINE_SRC_EVENT_WINDOWEVENT_H_
#define ENGINE_SRC_EVENT_WINDOWEVENT_H_

#include "core.h"
#include "event.h"

namespace engine {

// handle what happens when a window is closed
class PUB_API WindowClosedEvent: public Event {
 public:
  EVENT_INIT(EventType::WindowClosedEvent)

  void print(std::ostream &stream) const override {
    stream << get_name() << " ";
  }
};

// handle what happens if a window is brought into the foreground
class PUB_API WindowFocusedEvent: public Event {
 private:
  int _focus;

 public:
  EVENT_INIT(EventType::WindowFocusedEvent)

  WindowFocusedEvent(int focus) :
    _focus(focus) {}

  inline int get_focus() const {
    return _focus;
  }

  void print(std::ostream &stream) const override {
    stream << get_name() << " ";
  }
};

class PUB_API WindowMovedEvent: public Event {
 public:
  EVENT_INIT(EventType::WindowMovedEvent)

  void print(std::ostream &stream) const override {
    stream << get_name() << " ";
  }
};

// handle window resizing
class PUB_API WindowResizedEvent: public Event {
 private:
  float _width, _height;

 public:
  EVENT_INIT(EventType::WindowResizedEvent)

  WindowResizedEvent(float width, float height) :
    _width(width), _height(height) {}

  inline float get_width() const {
    return _width;
  }

  inline float get_height() const {
    return _height;
  }

  void print(std::ostream &stream) const override {
    stream << get_name() << ": " << get_width()
           << " x " << get_height() << " ";
  }
};

}  // namespace engine

#endif  // ENGINE_SRC_EVENT_WINDOWEVENT_H_
