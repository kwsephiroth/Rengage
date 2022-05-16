#include "Logger/Logger.h"

namespace RenGage
{
	Logger::Logger()
	{

	}

	Logger::~Logger()
	{
		if (m_logFile.is_open())
			m_logFile.close();
	}

	void Logger::OpenLogFile(const std::string fileame)
	{
	}

	std::string Logger::GetLogPrefix(const LogSeverity severity)
	{
		auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::stringstream ss;
		char timeCharBuff[26];
		ctime_s(timeCharBuff, sizeof timeCharBuff, &timenow);
		std::string timeStr = std::string(timeCharBuff);
		timeStr.erase(std::remove(timeStr.begin(), timeStr.end(), '\n'), timeStr.end());
		
		ss << "[ " << timeStr << " | " << GetLogSeverityString(severity) << " ] : ";

		return ss.str();
	}

	void Logger::LogMsgToFile(const LogSeverity severity, const std::string& msg)
	{
	}

	void Logger::LogMsgToConsole(const LogSeverity severity, const std::string& msg)
	{
		std::cout << GetLogPrefix(severity) << "{ " << msg << " }\n";
	}


}
