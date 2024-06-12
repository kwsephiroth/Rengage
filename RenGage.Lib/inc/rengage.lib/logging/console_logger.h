#pragma once
#include "../logging/ilogger.h"

namespace rengage::logging
{
	class ConsoleLogger final : public ILogger
	{
	public:
		ConsoleLogger() = default;
		void log(LogSeverity severity,
			std::string msg,
			std::source_location location = std::source_location::current()) override;
	};
}