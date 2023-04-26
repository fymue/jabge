#ifndef ENGINE_SRC_LOG_H_
#define ENGINE_SRC_LOG_H_

#include <memory>
#include "../../../cpplog/log.h"  // FIXME add include path in Makefile

namespace engine {

/*
 * wrapper aroung cpplog::Logger class for logging
 */
class PUB_API Log {
 private:
  static std::shared_ptr<cpplog::Logger> engine_log;
  static std::shared_ptr<cpplog::Logger> app_log;

 public:
  static void init() {
    Log::engine_log =
      std::shared_ptr<cpplog::Logger>(cpplog::create_log("ENGINE"));
    Log::engine_log->set_log_level(cpplog::Level::STANDARD);

    Log::app_log =
      std::shared_ptr<cpplog::Logger>(cpplog::create_log("APP"));
    Log::app_log->set_log_level(cpplog::Level::STANDARD);
  }

  inline static std::shared_ptr<cpplog::Logger> &get_engine_log() {
    return engine_log;
  }

  inline static std::shared_ptr<cpplog::Logger> &get_app_log() {
    return app_log;
  }
};

std::shared_ptr<cpplog::Logger> Log::engine_log;
std::shared_ptr<cpplog::Logger> Log::app_log;

}  // namespace engine

// macros to call logging functions
#define ENGINE_LOG_ERROR(...) engine::Log::get_engine_log()->error(__VA_ARGS__)
#define ENGINE_LOG_WARN(...)  engine::Log::get_engine_log()->warn(__VA_ARGS__)
#define ENGINE_LOG_INFO(...)  engine::Log::get_engine_log()->info(__VA_ARGS__)

#define APP_LOG_ERROR(...)    engine::Log::get_app_log()->error(__VA_ARGS__)
#define APP_LOG_WARN(...)     engine::Log::get_app_log()->warn(__VA_ARGS__)
#define APP_LOG_INFO(...)     engine::Log::get_app_log()->info(__VA_ARGS__)

#endif  // ENGINE_SRC_LOG_H_
