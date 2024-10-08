#include "logging/file_logger.h"

namespace rengage::logging
{

	FileLogger::FileLogger(std::string log_directory) :
		m_log_file_directory(log_directory)
	{
		init_log_file();
	}

	FileLogger::~FileLogger()
	{
		if(m_log_file.is_open())
			m_log_file.close();
	}

	bool FileLogger::is_initialized() const
	{
		return m_initialized;
	}

	bool FileLogger::open_log_file(const std::string file_name)
	{
		std::string full_filename = m_log_file_directory + file_name;

		m_log_file.open(full_filename, std::ios::app);

		if (m_log_file.fail()) {
			//log_to_console(LogSeverity::ERROR, "Failed to open file \"" + full_filename + "\"");
			return false;
		}
		return true;
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
		m_initialized = open_log_file(file_name);
	}

	void FileLogger::log(LogSeverity severity, std::string msg, std::source_location location)
	{
		//std::call_once(m_file_init_flag, &FileLogger::init_log_file, this);
		if (!m_initialized)
			return;
		auto log_prefix = get_log_prefix(severity, location);
		std::lock_guard<std::mutex> lock(m_log_file_mutex);
		m_log_file << log_prefix << "{ " << msg << " }\n";
	}
}