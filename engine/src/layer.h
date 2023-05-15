#ifndef ENGINE_SRC_LAYER_H_
#define ENGINE_SRC_LAYER_H_

#include <cstring>

#include "core.h"
#include "event/event.h"

namespace engine {

static constexpr uint8_t MAX_LAYER_NAME_LEN = 30;

/*
 * base class for a Layer;
 * each derived class should implement the "on_push"
 * and "on_pop" methods defining what should happen
 * whenever a layer is first pushed to/popped from
 * the layer stack; each derived class should also
 * implement the "on_update" method definining what
 * happens within the layer every new frame, as well
 * as the "on_event" method defining what happens if
 * an event is passed to and potentially handled by
 * the layer; in Debug mode, the can be given a name
 * for e.g. logging
 */
class PUB_API Layer {
 private:
#ifndef NDEBUG
  char _name[MAX_LAYER_NAME_LEN];
#endif

 public:
  Layer() {}

#ifndef NDEBUG
  explicit Layer(const char *name) {
    std::strncpy(_name, name, MAX_LAYER_NAME_LEN);
  }
#else
  explicit Layer(const char *name) {}
#endif

  virtual ~Layer() {}

  // ... when layer is pushed onto layer stack
  virtual void on_push() {}

  // ... when layer is popped from layer stack
  virtual void on_pop() {}

  // ... (every frame)
  virtual void on_update() {}

  // handle event in current layer
  virtual void on_event(Event *e) {}

#ifndef NDEBUG
  const char *get_name() const {
    return _name;
  }
#endif

  friend std::ostream &operator<<(std::ostream &stream, const Layer &layer) {
#ifndef NDEBUG
    stream << layer._name;
#endif
    return stream;
  }
};

}  // namespace engine

#endif  // ENGINE_SRC_LAYER_H_
