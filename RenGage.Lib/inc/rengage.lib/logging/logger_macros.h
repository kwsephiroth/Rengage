#pragma once
#include "logger.h"

using namespace rengage::logging;

#define LOG_INFO(msg)														\
{																			\
	Logger::get().log(LogSeverity::INFO, LogDestination::FILE, msg);	    \
	Logger::get().log(LogSeverity::INFO, LogDestination::CONSOLE, msg);		\
}

#define LOG_WARNING(msg)													\
{																			\
	Logger::get().log(LogSeverity::WARNING, LogDestination::FILE, msg);		\
	Logger::get().log(LogSeverity::WARNING, LogDestination::CONSOLE, msg);	\
}

#define LOG_ERROR(msg)														\
{																			\
	Logger::get().log(LogSeverity::ERROR, LogDestination::FILE, msg);		\
	Logger::get().log(LogSeverity::ERROR, LogDestination::CONSOLE, msg);	\
}

#define LOG_DEBUG(msg)														\
{																			\
	Logger::get().log(LogSeverity::DEBUG, LogDestination::FILE, msg);		\
	Logger::get().log(LogSeverity::DEBUG, LogDestination::CONSOLE, msg);	\
}

