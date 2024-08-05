#pragma once
#include "ilogger.h"

using namespace rengage::logging;

#define LOG_INFO(logger_ptr, msg)												\
{																				\
	logger_ptr->log(LogSeverity::INFO, msg);									\
}

#define LOG_WARNING(logger_ptr, msg)											\
{																				\
	logger_ptr->log(LogSeverity::WARNING, msg);									\
}

#define LOG_ERROR(logger_ptr, msg)												\
{																				\
	logger_ptr->log(LogSeverity::ERROR, msg);									\
}

#define LOG_DEBUG(logger_ptr, msg)												\
{																				\
	logger_ptr->log(LogSeverity::DEBUG, msg);									\
}

