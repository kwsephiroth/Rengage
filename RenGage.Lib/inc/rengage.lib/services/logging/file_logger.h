#pragma once
#include "../../interfaces/ilogger.h"

namespace rengage::services::logging
{
	const std::string LOG_FILE_DIRECTORY = "logs/";
	const std::string LOG_FILE_NAME_PREFIX = "RenGage.Log_";
	const std::string LOG_FILE_NAME_SUFFIX = ".log";

	class FileLogger final : public ILogger
	{
	public:
		FileLogger(std::string log_directory = LOG_FILE_DIRECTORY);
		~FileLogger();
		void log(
			LogSeverity severity,
			std::string msg,
			std::source_location location = std::source_location::current()) override;
		bool is_initialized() const;

	private:
		void init_log_file();
		bool open_log_file(const std::string file_name);

		std::ofstream m_log_file;
		std::string m_log_file_directory;
		std::once_flag m_file_init_flag;
		std::mutex m_log_file_mutex;
		bool m_initialized = false;
	};
}
