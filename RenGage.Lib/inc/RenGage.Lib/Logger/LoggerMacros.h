#pragma once
#define LOG_INFO(logger, msg)										\
{																	\
	logger.LogMsg(LogSeverity::INFO, LogDestination::FILE, msg);	\
}	

#define LOG_WARNING(logger, msg)									\
{																	\
	logger.LogMsg(LogSeverity::WARNING, LogDestination::FILE, msg);	\
}	

#define LOG_ERROR(logger, msg)										\
{																	\
	logger.LogMsg(LogSeverity::ERROR, LogDestination::FILE, msg);	\
}	

