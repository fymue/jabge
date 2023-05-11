#ifndef ENGINE_SRC_APPLICATION_H_
#define ENGINE_SRC_APPLICATION_H_

#include "core.h"
#include "window.h"
#include "log.h"
#include "layer.h"
#include "layerstack.h"

#include "event/event.h"
#include "event/windowevent.h"

#define BIND_EVENT(func) std::bind(&func, this, std::placeholders::_1)

namespace engine {

class PUB_API Application {
 private:
  Window *_window;
  bool _is_running;
  LayerStack _layers;

 public:
  Application();
  virtual ~Application();

  void run();

  bool on_window_close(WindowClosedEvent *e);

  void on_event(Event *e);

  void push_layer(Layer *layer);
  void pop_layer(Layer *layer);
  void push_overlay(Layer *layer);
  void pop_overlay(Layer *layer);
};

// should be implemented by program that uses the engine
// and initialize the main object of the program
Application* init();

}  // namespace engine

#endif  // ENGINE_SRC_APPLICATION_H_
