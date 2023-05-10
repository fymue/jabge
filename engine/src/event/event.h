#ifndef ENGINE_SRC_EVENT_EVENT_H_
#define ENGINE_SRC_EVENT_EVENT_H_

#include <string>
#include <ostream>
#include <functional>

#include "core.h"

namespace engine {

/*
 * Event types that can be handled by an application/window;
 * each variant has an identically-named class implementation
 * that contains relevant data for the specific event as well as
 * an "on_event" function that determines what happens if
 * a respective event was recorded
 */
enum class EventType {
  None,
  KeyPressedEvent, KeyReleasedEvent,
  WindowClosedEvent, WindowResizedEvent, WindowFocusedEvent, WindowMovedEvent,
  MousePressedEvent, MouseReleasedEvent, MouseMovedEvent, MouseScrolledEvent
};

// shared methods for every concrete event that implements
// the base "Event" class
#define EVENT_INIT(type) \
  static EventType TYPE() {return type;}; \
  EventType get_type() const override {return type;}; \
  const char *get_name() const override {return #type;};

/*
 * base Event type;
 * every implementation needs to implement
 * the "get_name" and "get_type" methods and provide
 * a "print" implementation so each event can be logged;
 * the "get_name" and "get_type" methods are implemented
 * using the "EVENT_TYPE(EventType::TYPE)" macro
 */
class PUB_API Event {
 private:
  bool _handled;

 protected:
  Event():
    _handled(false) {}

  virtual void print(std::ostream &stream) const = 0;

 public:
  friend class EventDispatcher;

  virtual const char *get_name() const = 0;
  virtual EventType get_type() const = 0;

  // each class that extends the base "Event" class should implement
  // the "print" method, which will be called in any event is logged
  friend std::ostream &operator<<(std::ostream &stream, const Event &event) {
    event.print(stream);
    return stream;
  }
};

// dispatches any event using the dispatch method,
// which calls class event-specific "on_event" function
class PUB_API EventDispatcher {
 private:
  Event *_event;

 public:
  EventDispatcher(Event *event) :
    _event(event) {}

  /*
   * dispatch the input on_event function if the event the dispatcher
   * was initialized with matches the input event of the provided on_event function;
   * this check is performed using the static "TYPE" method and the
   * object/event-specific "get_type" method; since the "TYPE" method is static,
   * it can be called directly and the template type "T"
   * (if the template type is a class/type that extends "Event")
   */
  template<typename T>
  bool dispatch(std::function<bool(T*)> on_event) {
    if (_event->get_type() == T::TYPE()) {
      /*
       * cast the event of the dispatcher to the concrete event type
       * the dispatch method was called with so the correct "on_event"
       * function can be called
       */
      T *concrete_event = dynamic_cast<T*>(_event);

      // call the event-specific "on_event" function
      // and update the handled boolean of the event
      bool handled = on_event(concrete_event);  // true if handled
      _event->_handled = handled;
    }

    return _event->_handled;  // false unless handled in if statement above
  }
};

}  // namespace engine

#endif  // ENGINE_SRC_EVENT_EVENT_H_
