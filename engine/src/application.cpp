#include "enginepch.h"
#include "application.h"

namespace engine {

Application *Application::_application = nullptr;
Input *Input::_input = nullptr;

Application::Application() :
  _window(nullptr), _is_running(false), _imgui_layer(nullptr) {
  if (!_application) {
    // create Application singleton
    _application = this;

    _window = Window::create(WindowProperties());

    /*
     * bind the Application::on_event function to every callback
     * function of the window, meaning that any event that is
     * created or received by the window is passed to
     * Application::on_event and is handled either directly or
     * by one of the layers on the layer stack
     */
    _window->set_event_callback(BIND_EVENT(Application::on_event));

    _imgui_layer = new ImGuiLayer(get_window_data());
    // // transfer ownership of ImGui layer to layer stack
    push_overlay(_imgui_layer);

    _is_running = true;
  }
}

Application::~Application() {
  delete _window;
}

void Application::push_layer(Layer *layer) {
  ENGINE_ASSERT(layer, "Layer passed to push_layer is NULL!");
  _layers.push(layer);
  layer->on_push();
}

void Application::pop_layer(Layer *layer) {
  ENGINE_ASSERT(layer, "Layer passed to pop_layer is NULL!");
  _layers.pop(layer);
  layer->on_pop();
}

void Application::push_overlay(Layer *layer) {
  ENGINE_ASSERT(layer, "Layer passed to push_overlay is NULL!");
  _layers.push_overlay(layer);
  layer->on_push();
}

void Application::pop_overlay(Layer *layer) {
  ENGINE_ASSERT(layer, "Layer passed to pop_overlay is NULL!");
  _layers.pop_overlay(layer);
  layer->on_pop();
}

/*
 * start main loop of the application;
 * this loop runs until e.g. the window is closed
 * and calls the "on_update" methods of all layers
 * and the window every frame
 */
void Application::run() {
  while (_is_running) {
    // run on_update for every layer (starting from lowest layer)
    for (Layer *layer : _layers) {
      ENGINE_ASSERT(layer, "Layer in layer stack is NULL!");
      layer->on_update();
    }

    // set up new ImGui frame that other layers can draw to
    ImGuiLayer *imgui_layer = dynamic_cast<ImGuiLayer*>(_imgui_layer);
    imgui_layer->begin_render();
    for (Layer *layer : _layers) {
      ENGINE_ASSERT(layer, "Layer in layer stack is NULL!");
      layer->on_imgui_render();
    }
    imgui_layer->end_render();  // draw ImGui frame

    // after all layers have been updated, update the window
    _window->on_update();
  }
}

bool Application::on_window_close(WindowClosedEvent *e) {
  // stop the main game loop
  _is_running = false;

  return true;
}
void Application::on_event(Event *e) {
  ENGINE_ASSERT(e, "Event passed to on_event function is NULL!");
  ENGINE_LOG_INFO(*e);

  EventDispatcher dispatcher(e);
  dispatcher.dispatch<WindowClosedEvent>(
    BIND_EVENT(Application::on_window_close));

  /*
   * run on_event for every layer in REVERSE ORDER,
   * starting with potential overlay layers,
   * so overlays can handle events first and potentially consume them;
   * the loop stops as soon as the event is handled, meaning once
   * an event is consumed, it isn't passed further down to a lower layer
   */
  for (auto layer = _layers.rbegin();
       !(e->is_handled()) && layer != _layers.rend(); layer++) {
    (*layer)->on_event(e);
  }
}

}  // namespace engine
