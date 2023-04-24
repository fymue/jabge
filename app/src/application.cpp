#include <iostream>
#include "engine.h"

class App: public engine::Application {
 public:
  App() {
    std::cerr << "created Sandbox app using engine\n";
  }

  ~App() {}
};

engine::Application *engine::init() {
  return new App();
}

