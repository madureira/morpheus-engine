#pragma once

#include <string>
#include "Engine/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "CustomLogSink.h"

namespace Morpheus {

	class Log
	{
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

	public:
		~Log();
		static void Init();
		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};

}

// Core log macros
#define ME_LOG_CORE_TRACE(...)    ::Morpheus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ME_LOG_CORE_INFO(...)     ::Morpheus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ME_LOG_CORE_WARN(...)     ::Morpheus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ME_LOG_CORE_ERROR(...)    ::Morpheus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ME_LOG_CORE_CRITICAL(...) ::Morpheus::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ME_LOG_CLIENT_TRACE(...)    ::Morpheus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ME_LOG_CLIENT_INFO(...)     ::Morpheus::Log::GetClientLogger()->info(__VA_ARGS__)
#define ME_LOG_CLIENT_WARN(...)     ::Morpheus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ME_LOG_CLIENT_ERROR(...)    ::Morpheus::Log::GetClientLogger()->error(__VA_ARGS__)
#define ME_LOG_CLIENT_CRITICAL(...) ::Morpheus::Log::GetClientLogger()->critical(__VA_ARGS__)

#ifdef MORPHEUS_APP
#define ME_LOG_TRACE    ME_LOG_CLIENT_TRACE
#define ME_LOG_INFO	    ME_LOG_CLIENT_INFO
#define ME_LOG_WARN	    ME_LOG_CLIENT_WARN
#define ME_LOG_ERROR    ME_LOG_CLIENT_ERROR
#define ME_LOG_CRITICAL ME_LOG_CLIENT_CRITICAL
#else
#define ME_LOG_TRACE    ME_LOG_CORE_TRACE
#define ME_LOG_INFO	    ME_LOG_CORE_INFO
#define ME_LOG_WARN	    ME_LOG_CORE_WARN
#define ME_LOG_ERROR    ME_LOG_CORE_ERROR
#define ME_LOG_CRITICAL ME_LOG_CORE_CRITICAL
#endif
