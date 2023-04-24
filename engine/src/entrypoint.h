#ifndef SRC_ENTRYPOINT_H_
#define SRC_ENTRYPOINT_H_

#include "application.h"

/*
 * Entrypoint of a program that uses the engine:
 * the program has to define the "engine::init" function,
 * which should create the object the program is based on,
 * which in turn should extend "engine::Application"
 */

extern engine::Application* engine::init();

int main(int argc, char **argv) {
  engine::Application *app = engine::init();
  app->run();
  delete app;
}
#endif  // SRC_ENTRYPOINT_H_