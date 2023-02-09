#pragma once

namespace rengage
{
	#define LOG_INFO(msg)										\
	{																	\
		logger::get().log(log_severity::INFO, log_destination::FILE, msg);	\
	}	

	#define LOG_WARNING(msg)									\
	{																	\
		logger::get().log(log_severity::WARNING, log_destination::FILE, msg);	\
	}	

	#define LOG_ERROR(msg)										\
	{																	\
		logger::get().log(log_severity::ERROR, log_destination::FILE, msg);	\
	}	
}

