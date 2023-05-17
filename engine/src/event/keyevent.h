#ifndef ENGINE_SRC_EVENT_KEYEVENT_H_
#define ENGINE_SRC_EVENT_KEYEVENT_H_

#include "../core.h"
#include "event.h"

namespace engine {

// base class for a key event (contains key code)
class PUB_API KeyEvent: public Event  {
 private:
  int _key_code;

 protected:
  KeyEvent(int key_code) :
    _key_code(key_code) {}

 public:
  inline int get_key_code() const {
    return _key_code;
  }
};

// handle what happens if a key is pressed or held
class PUB_API KeyPressedEvent: public KeyEvent {
 private:
  int _repeat_count;

 public:
  EVENT_INIT(EventType::KeyPressedEvent)

  KeyPressedEvent(int key_code, int repeat_count) :
    KeyEvent(key_code), _repeat_count(repeat_count) {}

  void print(std::ostream &stream) const override {
    stream << get_name() << ": " << get_key_code()
           << " (repeat: " << _repeat_count << ") ";
  }
};

// handle what happens if a key is released
class PUB_API KeyReleasedEvent: public KeyEvent {
 public:
  EVENT_INIT(EventType::KeyReleasedEvent)

  KeyReleasedEvent(int key_code):
    KeyEvent(key_code) {}

  void print(std::ostream &stream) const override {
    stream << get_name() << ": " << get_key_code() << " ";
  }
};

}  // namespace engine

#endif  // ENGINE_SRC_EVENT_KEYEVENT_H_
