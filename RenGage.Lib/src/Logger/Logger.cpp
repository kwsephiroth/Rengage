#include "logger/logger.h"

namespace rengage
{
	Logger::Logger(std::string log_directory) :
		m_log_file_directory(log_directory)
	{
		std::call_once(m_file_init_flag, &Logger::init_log_file, this);
	}

	Logger::~Logger()
	{
		if (m_log_file.is_open())
			m_log_file.close();
	}

	Logger& Logger::get()
	{
		static Logger log;
		return log;
	}

	void Logger::init_log_file()
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

	void Logger::open_log_file(const std::string file_name)
	{
		std::string full_filename = m_log_file_directory + file_name;

		m_log_file.open(full_filename, std::ios::app);

		if (m_log_file.fail()) {
			log_to_console(LogSeverity::ERROR, "Failed to open file \"" + full_filename + "\"");
		}
	}

	std::string Logger::get_log_prefix(const LogSeverity severity, std::string caller)
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
			<<  get_log_severity_str(severity) << " ] : ";

		return ss.str();
	}

	void Logger::log(LogSeverity severity, LogDestination destination, std::string msg, std::string caller)
	{
		switch (destination)
		{
			case LogDestination::CONSOLE: 
				log_to_console(severity, std::move(msg), std::move(caller));
				break;

			case LogDestination::FILE: 
				log_to_file(severity, std::move(msg), std::move(caller));
				break;
		}
	}

	void Logger::log_to_file(LogSeverity severity, std::string msg, std::string caller)
	{
		auto log_prefix = get_log_prefix(severity, caller);
		std::unique_lock<std::mutex>(m_log_file_mutex);
		m_log_file <<  log_prefix << "{ " << msg << " }\n";
	}

	void Logger::log_to_console(LogSeverity severity, std::string msg, std::string caller)
	{
		std::cout << get_log_prefix(severity, caller) << "{ " << msg << " }\n";
	}
}
