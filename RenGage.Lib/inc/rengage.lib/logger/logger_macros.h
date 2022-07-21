#pragma once
#define LOG_INFO(logger, msg)										\
{																	\
	logger.log(log_severity::INFO, log_destination::FILE, msg);	\
}	

#define LOG_WARNING(logger, msg)									\
{																	\
	logger.log(log_severity::WARNING, log_destination::FILE, msg);	\
}	

#define LOG_ERROR(logger, msg)										\
{																	\
	logger.log(log_severity::ERROR, log_destination::FILE, msg);	\
}	

