#include "logging/file_logger.h"

namespace rengage::logging
{
	void FileLogger::open_log_file(const std::string file_name)
	{
		std::string full_filename = m_log_file_directory + file_name;

		m_log_file.open(full_filename, std::ios::app);

		if (m_log_file.fail()) {
			//log_to_console(LogSeverity::ERROR, "Failed to open file \"" + full_filename + "\"");
		}
	}

	void FileLogger::init_log_file()
	{
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		std::stringstream filename_mid;
		filename_mid << (now->tm_mon + 1) << "_"
			<< now->tm_mday << "_"
			<< now->tm_year + 1900 << "_"
			<< t;

		std::filesystem::create_directory(m_log_file_directory);
		std::string file_name = LOG_FILE_NAME_PREFIX + filename_mid.str() + LOG_FILE_NAME_SUFFIX;
		open_log_file(file_name);
	}

	void FileLogger::log(LogSeverity severity, std::string msg, std::source_location location)
	{
		std::call_once(m_file_init_flag, &FileLogger::init_log_file, this);
		auto log_prefix = get_log_prefix(severity, location);
		std::unique_lock<std::mutex>(m_log_file_mutex);
		m_log_file << log_prefix << "{ " << msg << " }\n";
	}
}