#include "Logger/Logger.h"

namespace RenGage
{
	Logger::Logger(std::string logDirectory) :
		m_logFileDirectory(logDirectory)
	{
		std::call_once(m_fileInitFlag, &Logger::InitLogFile, this);
	}

	Logger::~Logger()
	{
		if (m_logFile.is_open())
			m_logFile.close();
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

		std::filesystem::create_directory(m_logFileDirectory);
		std::string filename = LOG_FILE_NAME_PREFIX + filenameMid.str() + LOG_FILE_NAME_SUFFIX;
		OpenLogFile(filename);
	}

	void Logger::OpenLogFile(const std::string filename)
	{
		std::string full_filename = m_logFileDirectory + filename;

		m_logFile.open(full_filename, std::ios::app);

		if (m_logFile.fail())
			LogMsgToConsole(LogSeverity::ERROR, "Failed to open file \"" + full_filename + "\"");
	}

	std::string Logger::GetLogPrefix(const LogSeverity severity, std::string caller)
	{
		auto sys_time_now = std::chrono::system_clock::now();
		auto timenow = std::chrono::system_clock::to_time_t(sys_time_now);
		auto ms_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(sys_time_now.time_since_epoch());
		std::stringstream ss;
		char timeStr[26];

		ctime_s(timeStr, sizeof timeStr, &timenow);

		for (int i = 0; i < 26; ++i)
		{
			if (timeStr[i] == '\n')
			{
				timeStr[i] = '\0';
				break;
			}
		}

		ss << "[ " << timeStr << " | "  << ms_since_epoch.count() << " (ms) | "
			<<  caller << " | "
			<<  GetLogSeverityString(severity) << " ] : ";

		return ss.str();
	}

	void Logger::LogMsg(LogSeverity severity, LogDestination destination, std::string msg, std::string caller)
	{
		switch (destination)
		{
			case LogDestination::CONSOLE:
			{
				LogMsgToConsole(severity, std::move(msg), std::move(caller));
			}
			break;

			case LogDestination::FILE:
			{
				LogMsgToFile(severity, std::move(msg), std::move(caller));
			}
			break;
		}
	}

	void Logger::LogMsgToFile(LogSeverity severity, std::string msg, std::string caller)
	{
		auto logPrefix = GetLogPrefix(severity, caller);
		std::unique_lock<std::mutex>(m_logFileMutex);
		m_logFile <<  logPrefix << "{ " << msg << " }\n";
	}

	void Logger::LogMsgToConsole(LogSeverity severity, std::string msg, std::string caller)
	{
		std::cout << GetLogPrefix(severity, caller) << "{ " << msg << " }\n";
	}


}
