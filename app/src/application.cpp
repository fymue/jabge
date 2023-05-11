#include <iostream>
#include "engine.h"

#include "layers.h"

class App: public engine::Application {
 public:
  App() {
    APP_LOG_INFO("CREATED SANDBOX APP USING ENGINE!");
    TestLayer * t = new TestLayer();
    t->on_update();
    push_layer(t);
  }

  ~App() {}
};

engine::Application *engine::init() {
  return new App();
}

