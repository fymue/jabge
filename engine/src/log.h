#ifndef ENGINE_SRC_LOG_H_
#define ENGINE_SRC_LOG_H_

#include "core.h"
#include "cpplog/cpplog.h"
#include "event/event.h"
#include "layer.h"

#ifndef NDEBUG
  #define __LOG_LEVEL cpplog::Level::DEBUG
#else
  #define __LOG_LEVEL cpplog::Level::STANDARD
#endif

namespace engine {

/*
 * extends cpplog::LoggerImpl with engine-specific types
 * so these types can be logged properly as well
 */
class PUB_API EngineLogImpl: public cpplog::LoggerImpl {
 public:
  using cpplog::LoggerImpl::log;
  using cpplog::LoggerImpl::parse_fmt_opts;

  EngineLogImpl();

  // log an event
  void log(std::ostream &stream, const Event &e, cpplog::LogFormat fmt);

  // log a layer
  void log(std::ostream &stream, const Layer &l, cpplog::LogFormat fmt);
};

typedef std::shared_ptr<cpplog::Logger<EngineLogImpl>> shared_log;

/*
 * wrapper aroung cpplog::Logger class for logging
 */
class PUB_API Log {
 private:
  static shared_log engine_log;
  static shared_log app_log;

 public:
  static void init();

  inline static shared_log &get_engine_log() {
    return engine_log;
  }

  inline static shared_log &get_app_log() {
    return app_log;
  }
};

}  // namespace engine

// macros to call logging functions
#define ENGINE_LOG_ERROR(...) engine::Log::get_engine_log()->error(__VA_ARGS__)
#define ENGINE_LOG_WARN(...)  engine::Log::get_engine_log()->warn(__VA_ARGS__)
#define ENGINE_LOG_INFO(...)  engine::Log::get_engine_log()->info(__VA_ARGS__)

#define APP_LOG_ERROR(...)    engine::Log::get_app_log()->error(__VA_ARGS__)
#define APP_LOG_WARN(...)     engine::Log::get_app_log()->warn(__VA_ARGS__)
#define APP_LOG_INFO(...)     engine::Log::get_app_log()->info(__VA_ARGS__)

#endif  // ENGINE_SRC_LOG_H_
