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
#include "LoggerMacros.h"

namespace RenGage
{
	const std::string LOG_FILE_NAME_PREFIX = "RenGage.Log_";
	const std::string LOG_FILE_NAME_SUFFIX = ".log";

	enum class LogSeverity
	{
		INFO,
		WARNING,
		ERROR
	};

	enum class LogDestination
	{
		CONSOLE,
		FILE
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

	//TODO: Make this class log to file only, not console.
	class Logger //Should this class actually be a Singleton instead? TODO: Determine.
	{
	public:
		Logger(std::string logDirectory = "Logs/");
		~Logger();
		void LogMsg(LogSeverity severity, LogDestination destination, std::string msg, std::string caller = __builtin_FUNCTION());
		void LogMsgToFile(LogSeverity severity, std::string msg, std::string caller = __builtin_FUNCTION());
		void LogMsgToConsole(LogSeverity severity, std::string msg, std::string caller = __builtin_FUNCTION());

	private:
		void InitLogFile();
		void OpenLogFile(const std::string filename);
		std::string GetLogPrefix(const LogSeverity severity, std::string caller);

		std::ofstream m_logFile;
		std::string m_logFileDirectory;
		std::once_flag m_fileInitFlag;
		static std::mutex m_logFileMutex;
	};																
}

