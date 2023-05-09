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

void Application::run() {
  while (_is_running) {
    _window->on_update();
  }
}

void Application::on_event(Event *e) {
  ENGINE_LOG_INFO(*e);
}

}  // namespace engine
