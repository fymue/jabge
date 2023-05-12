#include "enginepch.h"
#include "log.h"

namespace engine {

EngineLogImpl::EngineLogImpl() :
  LoggerImpl() {}

void EngineLogImpl::log(std::ostream &stream, const Event &e,
                        cpplog::LogFormat fmt) {
  parse_fmt_opts(stream, e, fmt);
}

std::shared_ptr<cpplog::Logger<EngineLogImpl>> Log::engine_log;
std::shared_ptr<cpplog::Logger<EngineLogImpl>> Log::app_log;

void Log::init() {
  engine_log = shared_log(cpplog::create_log("ENGINE", new EngineLogImpl()));
  engine_log->set_log_level(__LOG_LEVEL);

  app_log = shared_log(cpplog::create_log("APP", new EngineLogImpl()));
  app_log->set_log_level(__LOG_LEVEL);
}

}  // namespace engine
