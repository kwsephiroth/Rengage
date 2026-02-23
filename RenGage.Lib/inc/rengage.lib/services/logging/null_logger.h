#pragma once
#include "../../interfaces/ilogger.h"

namespace rengage::services::logging
{
	class NullLogger final : public ILogger
	{
		void log(LogSeverity severity,
			std::string msg,
			std::source_location location = std::source_location::current()) override
		{
		}
	};
}