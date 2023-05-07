#include <iostream>
#include "engine.h"

class App: public engine::Application {
 public:
  App() {
    ENGINE_LOG_INFO("CREATED SANDBOX APP USING ENGINE!");
  }

  ~App() {}
};

engine::Application *engine::init() {
  return new App();
}

