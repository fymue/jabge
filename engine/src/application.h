#ifndef ENGINE_SRC_APPLICATION_H_
#define ENGINE_SRC_APPLICATION_H_

#include "core.h"
#include "window.h"
#include "log.h"
#include "layer.h"
#include "layerstack.h"
#include "input.h"

#include "event/event.h"
#include "event/windowevent.h"

#include "layer/imguilayer.h"

namespace engine {

class PUB_API Application {
 private:
  Window *_window;
  bool _is_running;
  LayerStack _layers;

  // keep explicit ptr to an ImGuiLayer so each layer can do layer-specific
  // rendering with ImGui components when they are being rendered
  Layer *_imgui_layer;  // FIXME: why can't I declare this as an ImGuiLayer ptr?

  static Application *_application;

 protected:
  inline int get_window_width() const {
    return _window->get_width();
  }

  inline int get_window_height() const {
    return _window->get_height();
  }

 public:
  Application();
  virtual ~Application();

  void run();

  bool on_window_close(WindowClosedEvent *e);

  void on_event(Event *e);

  // add a layer to the top of the layer stack
  // (this transfers ownership of the layer to the layer stack)
  void push_layer(Layer *layer);

  // pop a layer from the layer stack (no-op if layer isn't found)
  void pop_layer(Layer *layer);

  // add an overlay layer to the layer stack;
  // these will always be inserted BEFORE any "regular" layer
  // (this transfers ownership of the layer to the layer stack)
  void push_overlay(Layer *layer);

  // pop an overlay layer from the layer stack
  void pop_overlay(Layer *layer);

  static inline const Application &get() {
    return *_application;
  }

  inline const Window &get_window() const {
    return *_window;
  }

  inline const WindowData &get_window_data() const {
    return _window->get_window_data();
  }
};

// initialize the main application;
// this function should be implemented by program that uses the engine
Application* init();

}  // namespace engine

#endif  // ENGINE_SRC_APPLICATION_H_
