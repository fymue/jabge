#include <iostream>
#include "engine.h"

#include "layers.h"

class App: public engine::Application {
 public:
  App() {
    APP_LOG_INFO("CREATED SANDBOX APP USING ENGINE!");
    push_layer(new TestLayer("Test Layer", get_window_data()));
    push_layer(new engine::ImGUILayer(get_window_data()));
  }

  ~App() {}
};

engine::Application *engine::init() {
  return new App();
}

