#pragma once

#include <spdlog/sinks/base_sink.h>

namespace Morpheus {

	struct LogColor final
	{
		float r, g, b, a;
	};

	class LogMessage final
	{
	public:
		enum class LogLevel
		{
			Invalid = -1,
			Trace = 0,
			Debug = 1,
			Info = 2,
			Warn = 3,
			Error = 4,
			Critical = 5,
			Off = 6, // Display nothing
		};

		LogMessage(const std::string& message = "", LogLevel level = LogLevel::Invalid)
			: m_Message(message)
			, m_Level(level)
		{
		}

		LogColor GetLogColor()
		{
			switch (m_Level)
			{
				case LogLevel::Trace: return { 0.75f, 0.75f, 0.75f, 1.00f };    // White-ish gray
				case LogLevel::Info: return { 0.20f, 0.70f, 0.20f, 1.00f };     // Green
				case LogLevel::Debug: return { 0.00f, 0.50f, 0.50f, 1.00f };    // Cyan
				case LogLevel::Warn: return { 1.00f, 1.00f, 0.00f, 1.00f };     // Yellow
				case LogLevel::Error: return { 1.00f, 0.00f, 0.00f, 1.00f };    // Red
				case LogLevel::Critical: return { 1.00f, 1.00f, 1.00f, 1.00f }; // White-white
				default: return { 1.00f, 1.00f, 1.00f, 1.00f };
			}
		}

		const std::string m_Message;
		const LogLevel m_Level;
	};

	template<typename Mutex>
	class CustomLogSink final : public spdlog::sinks::base_sink<Mutex>
	{
	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			spdlog::memory_buf_t formatted;
			base_sink<Mutex>::formatter_->format(msg, formatted);
			AddMessage(CreateRef<LogMessage>(fmt::to_string(formatted), GetMessageLevel(msg.level)));
		}

		void flush_() override
		{
			for (auto message = s_MessageBuffer.begin(); message != s_MessageBuffer.end(); message++)
			{
				(*message) = CreateRef<LogMessage>();
			}
			s_MessageBufferBegin = 0;
		}

		static LogMessage::LogLevel GetMessageLevel(const spdlog::level::level_enum level)
		{
			switch (level)
			{
				case spdlog::level::level_enum::trace: return LogMessage::LogLevel::Trace;
				case spdlog::level::level_enum::debug: return LogMessage::LogLevel::Debug;
				case spdlog::level::level_enum::info: return LogMessage::LogLevel::Info;
				case spdlog::level::level_enum::warn: return LogMessage::LogLevel::Warn;
				case spdlog::level::level_enum::err: return LogMessage::LogLevel::Error;
				case spdlog::level::level_enum::critical: return LogMessage::LogLevel::Critical;
				case spdlog::level::level_enum::off: return LogMessage::LogLevel::Off;
			}
			return LogMessage::LogLevel::Invalid;
		}

		static const char* GetLevelName(LogMessage::LogLevel level)
		{
			switch (level)
			{
				case LogMessage::LogLevel::Trace: return "Trace";
				case LogMessage::LogLevel::Info: return "Info";
				case LogMessage::LogLevel::Debug: return "Debug";
				case LogMessage::LogLevel::Warn: return "Warning";
				case LogMessage::LogLevel::Error: return "Error";
				case LogMessage::LogLevel::Critical: return "Critical";
				case LogMessage::LogLevel::Off: return "None";
				default: return "Unknown name";
			}
		}

		static void AddMessage(const Ref<LogMessage>& message)
		{
			if (message->m_Level == LogMessage::LogLevel::Invalid)
			{
				return;
			}

			*(s_MessageBuffer.begin() + s_MessageBufferBegin) = message;

			if (++s_MessageBufferBegin == s_MessageBufferCapacity)
			{
				s_MessageBufferBegin = 0;
			}

			if (s_MessageBufferSize < s_MessageBufferCapacity)
			{
				s_MessageBufferSize++;
			}

			if (s_AllowScrollingToBottom)
			{
				s_RequestScrollToBottom = true;
			}
		}

	public:
		static uint16_t s_MessageBufferCapacity;
		static uint16_t s_MessageBufferSize;
		static uint16_t s_MessageBufferBegin;
		static std::vector<Ref<LogMessage>> s_MessageBuffer;
		static bool s_AllowScrollingToBottom;
		static bool s_RequestScrollToBottom;
	};

}

#include <spdlog/details/null_mutex.h>
#include <mutex>
namespace Morpheus {
	using CustomLogSink_mt = CustomLogSink<std::mutex>;
	using CustomLogSink_st = CustomLogSink<spdlog::details::null_mutex>;

	uint16_t CustomLogSink_mt::s_MessageBufferCapacity = 200;
	uint16_t CustomLogSink_mt::s_MessageBufferSize = 0;
	uint16_t CustomLogSink_mt::s_MessageBufferBegin = 0;
	std::vector<Ref<LogMessage>> CustomLogSink_mt::s_MessageBuffer = std::vector<Ref<LogMessage>>(200);
	bool CustomLogSink_mt::s_AllowScrollingToBottom = true;
	bool CustomLogSink_mt::s_RequestScrollToBottom = false;
}
