#pragma once
#include "logger.h"


#define LOG_INFO(msg)																				\
{																									\
	rengage::Logger::get().log(rengage::LogSeverity::INFO, rengage::LogDestination::FILE, msg);	    \
	rengage::Logger::get().log(rengage::LogSeverity::INFO, rengage::LogDestination::CONSOLE, msg);  \
}

#define LOG_WARNING(msg)																				\
{																										\
	rengage::Logger::get().log(rengage::LogSeverity::WARNING, rengage::LogDestination::FILE, msg);		\
	rengage::Logger::get().log(rengage::LogSeverity::WARNING, rengage::LogDestination::CONSOLE, msg);	\
}

#define LOG_ERROR(msg)																				\
{																									\
	rengage::Logger::get().log(rengage::LogSeverity::ERROR, rengage::LogDestination::FILE, msg);	\
	rengage::Logger::get().log(rengage::LogSeverity::ERROR, rengage::LogDestination::CONSOLE, msg);	\
}

#define LOG_DEBUG(msg)																				\
{																									\
	rengage::Logger::get().log(rengage::LogSeverity::DEBUG, rengage::LogDestination::FILE, msg);	\
	rengage::Logger::get().log(rengage::LogSeverity::DEBUG, rengage::LogDestination::CONSOLE, msg);	\
}

