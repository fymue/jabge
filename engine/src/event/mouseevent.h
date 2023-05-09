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
 public:
  EVENT_INIT(MousePressedEvent)

  MousePressedEvent(int button_code):
    MouseButtonEvent(button_code) {}

  void print(std::ostream &stream) const override {
    stream << get_name() << " (Button: " << get_button_code() << " ";
  }
};

class PUB_API MouseReleasedEvent: public MouseButtonEvent {
 public:
  EVENT_INIT(MouseReleasedEvent)

  MouseReleasedEvent(int button_code):
    MouseButtonEvent(button_code) {}

  void print(std::ostream &stream) const override {
    stream << get_name() << "(Button: " << get_button_code() << ") ";
  }
};

class PUB_API MouseMovedEvent: public Event {
 private:
  double _x_pos, _y_pos;

 public:
  EVENT_INIT(MouseMovedEvent)

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

class PUB_API MouseScrolledEvent: public Event {
 private:
  double _x_offset, _y_offset;

 public:
  EVENT_INIT(MouseScrolledEvent)

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
