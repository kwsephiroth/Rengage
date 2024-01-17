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

#define DEBUG_MODE 1

namespace rengage::logging
{
	const std::string LOG_FILE_DIRECTORY = "Logs/";
	const std::string LOG_FILE_NAME_PREFIX = "RenGage.Log_";
	const std::string LOG_FILE_NAME_SUFFIX = ".log";

	enum class LogSeverity
	{
		INFO,
		WARNING,
		ERROR,
		DEBUG
	};

	enum class LogDestination
	{
		CONSOLE,
		FILE
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

	class Logger final
	{
	public:
		~Logger();

		static Logger& get();

		//Disable moving and copying
		Logger(Logger const&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		//TODO: Determine how portable GCC builtin function is
		//TODO: Add support for caller's line number and file name
		void log(LogSeverity severity,
				 LogDestination destination,
				 std::string msg,
				 std::source_location location = std::source_location::current());

		void log_to_file(LogSeverity severity,
						 std::string msg,
						 std::source_location location = std::source_location::current());

		void log_to_console(LogSeverity severity,
							std::string msg,
							std::source_location location = std::source_location::current());

	private:
		Logger(std::string log_directory = LOG_FILE_DIRECTORY);
		void init_log_file();
		void open_log_file(const std::string file_name);
		std::string get_log_prefix(const LogSeverity severity, const std::source_location& location);

		std::ofstream m_log_file;
		std::string m_log_file_directory;
		std::once_flag m_file_init_flag;//TODO: When this is static, the log buffer is never flushed and file is empty. Figure out why.
		std::mutex m_log_file_mutex;//inline OK since C++17
	};																
}

