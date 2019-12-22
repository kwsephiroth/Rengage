#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>

namespace RenGageAPI
{
	namespace Utilities
	{
		enum class Severity
		{
			Info,
			Warning,
			Error,
			Critical
		};

		static std::string GetSeverityStr(const Severity severity)
		{
			switch (severity)
			{
			case Severity::Info:
				return "Info : ";

			case Severity::Error:
				return "Error : ";

			case Severity::Warning:
				return "Warning : ";

			case Severity::Critical: 
				return "Critical : ";

			default:
				return "Info : ";
			}
		}

		class Logger//TODO: Make this a singleton class?
		{
		private:
			Logger() = default;
			
		public:
			~Logger() = default;

			static void WriteMessageToConsole(const std::string& msg, const Severity severity = Severity::Info)//, const char* file = "", const int line = 0)
			{
				//std::cout << file << " : line(" << line << ") : " << GetSeverityStr(severity) << msg << std::endl;
				std::cout << GetSeverityStr(severity) << msg << std::endl;
			}

			//TODO: Write function that logs messages to file 
			//ex) write to file at path "$(current directory)/logs/RenGageAPI.log"
		};

		//#define	LOG_TO_CONSOLE( message, severity ) Logger::WriteMessageToConsole(message, severity, __FILE__, __LINE__)
	}
}