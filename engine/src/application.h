#ifndef ENGINE_SRC_APPLICATION_H_
#define ENGINE_SRC_APPLICATION_H_

#include "core.h"
#include "window.h"

namespace engine {

class PUB_API Application {
 private:
  Window *_window;
  bool _is_running;

 public:
  Application();
  virtual ~Application();

  void run();
};

// should be implemented by program that uses the engine
// and initialize the main object of the program
Application* init();

}  // namespace engine

#endif  // ENGINE_SRC_APPLICATION_H_
