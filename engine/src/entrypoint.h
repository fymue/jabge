#ifndef ENGINE_SRC_ENTRYPOINT_H_
#define ENGINE_SRC_ENTRYPOINT_H_

#include "application.h"
#include "log.h"

/*
 * Entrypoint of a program that uses the engine:
 * the program has to define the "engine::init" function,
 * which should create the object the program is based on,
 * which in turn should extend "engine::Application"
 */

extern engine::Application* engine::init();

int main(int argc, char **argv) {
  engine::Log::init();

  engine::Application *app = engine::init();
  ENGINE_ASSERT(app, "Failed to initialize Application!");

  app->run();

  delete app;
}

#endif  // ENGINE_SRC_ENTRYPOINT_H_
