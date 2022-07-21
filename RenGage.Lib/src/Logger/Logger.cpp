#include "Logger/Logger.h"

namespace RenGage
{
	Logger::Logger(std::string logDirectory) :
		m_log_file_directory(logDirectory)
	{
		std::call_once(m_file_init_flag, &Logger::InitLogFile, this);
	}

	Logger::~Logger()
	{
		if (m_log_file.is_open())
			m_log_file.close();
	}

	void Logger::InitLogFile()
	{
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		std::stringstream filenameMid;
		filenameMid << (now->tm_mon + 1) << "_"
			<< now->tm_mday << "_"
			<< now->tm_year << "_"
			<< t;

		std::filesystem::create_directory(m_log_file_directory);
		std::string filename = LOG_FILE_NAME_PREFIX + filenameMid.str() + LOG_FILE_NAME_SUFFIX;
		OpenLogFile(filename);
	}

	void Logger::OpenLogFile(const std::string filename)
	{
		std::string full_filename = m_log_file_directory + filename;

		m_log_file.open(full_filename, std::ios::app);

		if (m_log_file.fail()) {
			LogMsgToConsole(LogSeverity::ERROR, "Failed to open file \"" + full_filename + "\"");
		}
	}

	std::string Logger::GetLogPrefix(const LogSeverity severity, std::string caller)
	{
		auto sys_time_now = std::chrono::system_clock::now();
		auto time_now = std::chrono::system_clock::to_time_t(sys_time_now);
		auto ms_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(sys_time_now.time_since_epoch());
		std::stringstream ss;
		char time_str[26];

		ctime_s(time_str, sizeof time_str, &time_now);

		for (int i = 0; i < sizeof(time_str); ++i) {
			if (time_str[i] == '\n')
			{
				time_str[i] = '\0';
				break;
			}
		}

		ss << "[ " << time_str << " | "  << ms_since_epoch.count() << " (ms) | "
			<<  caller << " | "
			<<  GetLogSeverityString(severity) << " ] : ";

		return ss.str();
	}

	void Logger::LogMsg(LogSeverity severity, LogDestination destination, std::string msg, std::string caller)
	{
		switch (destination)
		{
			case LogDestination::CONSOLE: 
				LogMsgToConsole(severity, std::move(msg), std::move(caller));
				break;

			case LogDestination::FILE: 
				LogMsgToFile(severity, std::move(msg), std::move(caller));
				break;
		}
	}

	void Logger::LogMsgToFile(LogSeverity severity, std::string msg, std::string caller)
	{
		auto logPrefix = GetLogPrefix(severity, caller);
		std::unique_lock<std::mutex>(m_logFileMutex);
		m_log_file <<  logPrefix << "{ " << msg << " }\n";
	}

	void Logger::LogMsgToConsole(LogSeverity severity, std::string msg, std::string caller)
	{
		std::cout << GetLogPrefix(severity, caller) << "{ " << msg << " }\n";
	}


}
