#ifndef ENGINE_SRC_APPLICATION_H_
#define ENGINE_SRC_APPLICATION_H_

#include "core.h"

namespace engine {

class PUB_API Application {
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
