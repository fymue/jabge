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
  // FIXME add proper engine init function and move this there
  engine::Log::init();

  engine::Application *app = engine::init();
  ENGINE_LOG_ERROR(1);
  ENGINE_LOG_WARN(3.14);
  ENGINE_LOG_INFO(3000);
  ENGINE_LOG_INFO(1000, cpplog::LogFmt::TYPE_SIZE | cpplog::NEWLINE);
  app->run();
  delete app;
}

#endif  // ENGINE_SRC_ENTRYPOINT_H_
