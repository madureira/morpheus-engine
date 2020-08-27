#include "mepch.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Morpheus {

    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    Log::~Log()
    {
        this->s_CoreLogger.reset();
        this->s_ClientLogger.reset();
        spdlog::shutdown();
    }

    void Log::Init()
    {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks.emplace_back(std::make_shared<CustomLogSink_mt>());

        // create the loggers
        s_CoreLogger = std::make_shared<spdlog::logger>("CORE", begin(sinks), end(sinks));
        spdlog::register_logger(s_CoreLogger);
        s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(sinks), end(sinks));
        spdlog::register_logger(s_ClientLogger);

        // configure the loggers
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger->set_level(spdlog::level::trace);
        s_ClientLogger->set_level(spdlog::level::trace);
    }

}
