#pragma once
#include "logger.h"


#define LOG_INFO(msg)																				\
{																									\
	rengage::logger::get().log(rengage::log_severity::INFO, rengage::log_destination::FILE, msg);	\
}	

#define LOG_WARNING(msg)																				\
{																										\
	rengage::logger::get().log(rengage::log_severity::WARNING, rengage::log_destination::FILE, msg);	\
}	

#define LOG_ERROR(msg)																				\
{																									\
	rengage::logger::get().log(rengage::log_severity::ERROR, rengage::log_destination::FILE, msg);	\
}	

