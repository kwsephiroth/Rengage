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
#include "logger_macros.h"

namespace rengage
{
	const std::string LOG_FILE_NAME_PREFIX = "RenGage.Log_";
	const std::string LOG_FILE_NAME_SUFFIX = ".log";

	enum class log_severity
	{
		INFO,
		WARNING,
		ERROR
	};

	enum class log_destination
	{
		CONSOLE,
		FILE
	};

	static std::string get_log_severity_str(const log_severity severity)
	{
		switch (severity)
		{
			case log_severity::INFO:
				return "INFO";

			case log_severity::WARNING:
				return "WARNING";

			case log_severity::ERROR:
				return "ERROR";

			default:
				return "UNKNOWN";
		}
	}

	//TODO: Make this class log to file only, not console.
	class logger //Should this class actually be a Singleton instead? TODO: Determine.
	{
	public:
		logger(std::string log_directory = "Logs/");
		~logger();
		void log(log_severity severity, log_destination destination, std::string msg, std::string caller = __builtin_FUNCTION());
		void log_to_file(log_severity severity, std::string msg, std::string caller = __builtin_FUNCTION());
		void log_to_console(log_severity severity, std::string msg, std::string caller = __builtin_FUNCTION());

	private:
		void init_log_file();
		void open_log_file(const std::string file_name);
		std::string get_log_prefix(const log_severity severity, std::string caller);

		std::ofstream m_log_file;
		std::string m_log_file_directory;
		std::once_flag m_file_init_flag;
		static std::mutex m_log_file_mutex;
	};																
}

