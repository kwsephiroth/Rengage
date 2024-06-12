#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <ctime>
#include <mutex>
#include <filesystem>
#include <source_location>//(since C++20)

namespace rengage::logging
{
	enum class LogSeverity
	{
		INFO,
		WARNING,
		ERROR,
		DEBUG
	};

	static std::string log_severity_to_str(const LogSeverity severity)
	{
		switch (severity)
		{
		case LogSeverity::WARNING:
			return "WARNING";

		case LogSeverity::ERROR:
			return "ERROR";

		case LogSeverity::DEBUG:
			return "DEBUG";

		case LogSeverity::INFO:
		default:
			return "INFO";
		}
	}

	class ILogger
	{
	public:
		virtual ~ILogger() = default;
		virtual void log(LogSeverity severity,
						 std::string msg,
						 std::source_location location) = 0;
	protected:
		std::string get_log_prefix(const LogSeverity severity, const std::source_location& location);
	};
}