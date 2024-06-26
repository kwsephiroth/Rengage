#pragma once
#include "../logging/ilogger.h"

namespace rengage::logging
{
	const std::string LOG_FILE_DIRECTORY = "Logs/";
	const std::string LOG_FILE_NAME_PREFIX = "RenGage.Log_";
	const std::string LOG_FILE_NAME_SUFFIX = ".log";

	class FileLogger final : public ILogger 
	{
	public:
		FileLogger(std::string log_directory = LOG_FILE_DIRECTORY);
		void log(LogSeverity severity,
			std::string msg,
			std::source_location location = std::source_location::current()) override;
	private:
		void init_log_file();
		void open_log_file(const std::string file_name);

		std::ofstream m_log_file;
		std::string m_log_file_directory;
		std::once_flag m_file_init_flag;//TODO: When this is static, the log buffer is never flushed and file is empty. Figure out why.
		std::mutex m_log_file_mutex;//inline OK since C++17
	};
}
