#ifndef ENGINE_SRC_EVENT_EVENT_H_
#define ENGINE_SRC_EVENT_EVENT_H_

#include <string>
#include <ostream>
#include <functional>

#include "../core.h"

namespace engine {

#define EVENT_INIT(type) \
  static EventType get_type() {return EventType::type;}; \
  const char *get_name() const override {return #type;}; \
  friend std::ostream &operator<<(std::ostream &stream, const type &event);

enum class EventType {
  None,
  KeyPressedEvent, KeyReleasedEvent,
  WindowClosedEvent, WindowResizedEvent, WindowFocusedEvent, WindowMovedEvent,
  MousePressedEvent, MouseReleasedEvent, MouseMovedEvent, MouseScrolledEvent
};

/*
 * base Event type
 * every implementation needs to implement
 * the get_name method and provide an operator<< overload;
 */
class PUB_API Event {
 private:
  bool _handled;

 protected:
  Event():
    _handled(false) {}

 public:
  friend class EventDispatcher;

  virtual const char* get_name() const = 0;
  friend std::ostream &operator<<(std::ostream &stream, const Event &event);
};

// dispatches any event using the dispatch method,
// which calls class event-specific "onEvent" function
class PUB_API EventDispatcher {
 private:
  Event *_event;

 public:
  EventDispatcher(Event *event) :
    _event(event) {}

  template<typename T>
  bool dispatch(std::function<bool(T*)> on_event) {
    _event->_handled = on_event(dynamic_cast<T*>(_event));
    return _event->_handled;
  }
};

}  // namespace engine

#endif  // ENGINE_SRC_EVENT_EVENT_H_
