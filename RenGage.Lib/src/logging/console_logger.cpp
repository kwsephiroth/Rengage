#include "logging/console_logger.h"

namespace rengage::logging
{
	void ConsoleLogger::log(LogSeverity severity, std::string msg, std::source_location location)
	{
		std::cout << get_log_prefix(severity, location) << "{ " << msg << " }\n";
	}
}