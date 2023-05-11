#include "enginepch.h"
#include "application.h"

namespace engine {

Application::Application() :
  _window(nullptr), _is_running(false) {
  _window = Window::create(WindowProperties());
  _window->set_event_callback(BIND_EVENT(Application::on_event));
  _is_running = true;
}

Application::~Application() {
  delete _window;
}

void Application::push_layer(Layer *layer) {
  _layers.push(layer);
}

void Application::pop_layer(Layer *layer) {
  _layers.pop(layer);
}

void Application::push_overlay(Layer *layer) {
  _layers.push_overlay(layer);
}

void Application::pop_overlay(Layer *layer) {
  _layers.pop_overlay(layer);
}

void Application::run() {
  while (_is_running) {
    // run on_update for every layer
    for (Layer *layer : _layers) {
      layer->on_update();
    }

    // update the window
    _window->on_update();
  }
}

bool Application::on_window_close(WindowClosedEvent *e) {
  // stop the main game loop
  _is_running = false;

  return true;
}
void Application::on_event(Event *e) {
  ENGINE_LOG_INFO(*e);

  EventDispatcher dispatcher(e);
  dispatcher.dispatch<WindowClosedEvent>(
    BIND_EVENT(Application::on_window_close));

  /*
   * run on_event for every layer in reverse order,
   * starting with potential overlay layers,
   * so overlays can handle events and potentially consume them;
   * the loop stops as soon as the event is handled
   */
  for (auto layer = _layers.rbegin();
       !(e->is_handled()) && layer != _layers.rend(); --layer) {
    (*layer)->on_event(e);
  }
}

}  // namespace engine
