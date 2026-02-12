#pragma once
#include "ilogger.h"
#include "../service_locator.h"

#define FETCH_LOGGER_SERVICE() auto logger_service_ptr = rengage::services::ServiceLocator::get_service<rengage::services::logging::ILogger>();																											\

#define LOG_INFO(msg)																\
{																					\
	FETCH_LOGGER_SERVICE()															\
	logger_service_ptr->log(rengage::services::logging::LogSeverity::INFO, msg);	\
}

#define LOG_WARNING(msg)															\
{																					\
	FETCH_LOGGER_SERVICE()															\
	logger_service_ptr->log(rengage::services::logging::LogSeverity::WARNING, msg);	\
}

#define LOG_ERROR(msg)																\
{																					\
	FETCH_LOGGER_SERVICE()															\
	logger_service_ptr->log(rengage::services::logging::LogSeverity::ERROR, msg);	\
}

#define LOG_DEBUG(msg)																\
{																					\
	FETCH_LOGGER_SERVICE()															\
	logger_service_ptr->log(rengage::services::logging::LogSeverity::DEBUG, msg);	\
}

