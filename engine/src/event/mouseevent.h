#ifndef ENGINE_SRC_EVENT_MOUSEEVENT_H_
#define ENGINE_SRC_EVENT_MOUSEEVENT_H_

#include "core.h"
#include "event.h"

namespace engine {

// base event for a mouse button press
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

// handle what happens if a mouse button is pressed
class PUB_API MousePressedEvent: public MouseButtonEvent {
 public:
  EVENT_INIT(EventType::MousePressedEvent)

  MousePressedEvent(int button_code):
    MouseButtonEvent(button_code) {}

  void print(std::ostream &stream) const override {
    stream << get_name() << " (Button: " << get_button_code() << " ";
  }
};

// handle what happens if a mouse button is released
class PUB_API MouseReleasedEvent: public MouseButtonEvent {
 public:
  EVENT_INIT(EventType::MouseReleasedEvent)

  MouseReleasedEvent(int button_code):
    MouseButtonEvent(button_code) {}

  void print(std::ostream &stream) const override {
    stream << get_name() << "(Button: " << get_button_code() << ") ";
  }
};

// handle what happens if the mouse is moved
class PUB_API MouseMovedEvent: public Event {
 private:
  double _x_pos, _y_pos;

 public:
  EVENT_INIT(EventType::MouseMovedEvent)

  MouseMovedEvent(double x_pos, double y_pos):
    _x_pos(x_pos), _y_pos(y_pos) {}

  inline double get_x_pos() const {
    return _x_pos;
  }

  inline double get_y_pos() const {
    return _y_pos;
  }

  void print(std::ostream &stream) const override {
    stream << get_name() << ": x_pos = "
           << _x_pos << ", y_pos = " << _y_pos << " ";
  }
};

// handle what happens if the user scrolled inside the application
class PUB_API MouseScrolledEvent: public Event {
 private:
  double _x_offset, _y_offset;

 public:
  EVENT_INIT(EventType::MouseScrolledEvent)

  MouseScrolledEvent(double x, double y):
    _x_offset(x), _y_offset(y) {}

  inline double get_x_offset() const {
    return _x_offset;
  }

  inline double get_y_offset() const {
    return _y_offset;
  }

  void print(std::ostream &stream) const override {
    stream << get_name() << ": x = "
           << _x_offset << ", y = " << _y_offset << " ";
  }
};

}  // namespace engine

#endif  // ENGINE_SRC_EVENT_MOUSEEVENT_H_
