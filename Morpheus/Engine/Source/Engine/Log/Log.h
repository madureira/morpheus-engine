#pragma once

#include "Engine/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Morpheus {

	class Log
	{
	public:
		static void Init();
		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define ME_CORE_TRACE(...)    ::Morpheus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ME_CORE_INFO(...)     ::Morpheus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ME_CORE_WARN(...)     ::Morpheus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ME_CORE_ERROR(...)    ::Morpheus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ME_CORE_CRITICAL(...) ::Morpheus::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ME_TRACE(...)         ::Morpheus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ME_INFO(...)          ::Morpheus::Log::GetClientLogger()->info(__VA_ARGS__)
#define ME_WARN(...)          ::Morpheus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ME_ERROR(...)         ::Morpheus::Log::GetClientLogger()->error(__VA_ARGS__)
#define ME_CRITICAL(...)      ::Morpheus::Log::GetClientLogger()->critical(__VA_ARGS__)
