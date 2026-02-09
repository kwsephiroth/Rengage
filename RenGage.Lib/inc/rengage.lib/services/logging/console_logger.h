#pragma once
#include "ilogger.h"

namespace rengage::services::logging
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