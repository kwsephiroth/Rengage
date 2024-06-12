#include "logging/ilogger.h"

namespace rengage::logging
{
	std::string ILogger::get_log_prefix(const LogSeverity severity, const std::source_location& location)
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

		//TODO: Move this filename extraction logic to dedicated, stand-alone function.
		std::string file_path = location.file_name();
		std::string file_name_only;
		int name_start_index = -1;
		if (!file_path.empty())
		{
			for (int i = file_path.size() - 1; i >= 0; --i)
			{
				if (file_path[i] == '/' || file_path[i] == '\\')
				{
					name_start_index = i + 1;
					break;
				}
			}
		}

		if (name_start_index)
		{
			file_name_only = file_path.substr(name_start_index);
		}

		ss << "[ " << time_str << " | " << ms_since_epoch.count() << " (ms) | "
			<< file_name_only << '(' << location.line() << ") '" << location.function_name() << "' | "
			<< log_severity_to_str(severity) << " ] : ";

		return ss.str();
	}
}