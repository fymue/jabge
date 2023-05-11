#ifndef ENGINE_SRC_LAYER_H_
#define ENGINE_SRC_LAYER_H_

#include "core.h"
#include "event/event.h"

namespace engine {

class PUB_API Layer {
 public:
  Layer() {}
  virtual ~Layer() {}

  // ... when layer is pushed onto layer stack
  virtual void on_push() {}

  // ... when layer is popped from layer stack
  virtual void on_pop() {}

  // ... (every frame)
  virtual void on_update() {}

  // handle event in current layer
  virtual void on_event(Event *e) {}
};

}  // namespace engine

#endif  // ENGINE_SRC_LAYER_H_
