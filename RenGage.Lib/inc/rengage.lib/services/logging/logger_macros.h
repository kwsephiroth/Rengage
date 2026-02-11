#pragma once
#include "ilogger.h"
#include "../service_locator.h"

#define LOG_INFO(logger_ptr, msg)												\
{																				\
	logger_ptr->log(rengage::services::logging::LogSeverity::INFO, msg);									\
}

#define LOG_WARNING(logger_ptr, msg)											\
{																				\
	logger_ptr->log(rengage::services::logging::LogSeverity::WARNING, msg);									\
}

#define LOG_ERROR(logger_ptr, msg)												\
{																				\
	logger_ptr->log(rengage::services::logging::LogSeverity::ERROR, msg);									\
}

#define LOG_DEBUG(logger_ptr, msg)												\
{																				\
	logger_ptr->log(rengage::services::logging::LogSeverity::DEBUG, msg);									\
}

