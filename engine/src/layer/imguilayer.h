#ifndef ENGINE_SRC_LAYER_IMGUILAYER_H_
#define ENGINE_SRC_LAYER_IMGUILAYER_H_

#include "core.h"
#include "layer.h"
#include "event/event.h"
#include "opengl/imguirenderer.h"

namespace engine {

class PUB_API ImGUILayer: public Layer {
 public:
  ImGUILayer() :
    Layer("ImGUILayer") {}

  ~ImGUILayer() {}

  void on_push();

  void on_pop();

  void on_update();

  void on_event(Event *e);
};

}  // namespace engine

#endif  // ENGINE_SRC_LAYER_IMGUILAYER_H_
