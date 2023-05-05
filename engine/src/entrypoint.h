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
  APP_LOG_INFO("this is a test string", cpplog::VERBOSE | cpplog::TYPE_SIZE | cpplog::NAME);
  ENGINE_LOG_WARN(std::array<long, 11>{1,2,3, 4, 5, 6, 7, 8, 9, 10, 11});
  ENGINE_LOG_ERROR(std::map<std::string, int>{{"z", 1}, {"b", 100}, {"c", 1000}, {"d", 1}, {"e", 100}, {"f", 1000}, {"g", 1}, {"h", 100}, {"j", 1000}, {"i", 1}, {"k", 100}, {"l", 1000}});
  ENGINE_LOG_INFO(std::unordered_map<std::string, int>{{"z", 1}, {"b", 100}, {"c", 1000}, {"d", 1}, {"e", 100}, {"f", 1000}, {"g", 1}, {"h", 100}, {"j", 1000}, {"i", 1}, {"k", 100}, {"l", 1000}});
  APP_LOG_ERROR(std::pair<std::string, std::map<std::string, int>>{"test", {{"key", 1000}}});
  APP_LOG_ERROR(std::pair<std::string,  int>{"test", 100});
  app->run();
  delete app;
}

#endif  // ENGINE_SRC_ENTRYPOINT_H_
