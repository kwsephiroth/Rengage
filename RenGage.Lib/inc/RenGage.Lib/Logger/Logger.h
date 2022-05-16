#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <algorithm>

namespace RenGage
{
	enum class LogSeverity
	{
		INFO,
		WARNING,
		ERROR
	};

	static std::string GetLogSeverityString(const LogSeverity severity)
	{
		switch (severity)
		{
			case LogSeverity::INFO:
			{
				return "INFO";
			}
			break;

			case LogSeverity::WARNING:
			{
				return "WARNING";
			}
			break;

			case LogSeverity::ERROR:
			{
				return "ERROR";
			}
			break;

			default:
				return "UNKNOWN";
		}
	}

	class Logger
	{
	public:
		Logger();
		~Logger();
		void LogMsgToFile(const LogSeverity severity, const std::string& msg);
		void LogMsgToConsole(const LogSeverity severity, const std::string& msg);

	private:
		void OpenLogFile(const std::string fileame);
		std::string GetLogPrefix(const LogSeverity severity);

		std::ofstream m_logFile;
	};
}

