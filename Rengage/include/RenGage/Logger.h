#pragma once
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

		std::string GetSeverityStr(const Severity severity)
		{
			switch (severity)
			{
			case Severity::Info:
				return "Info : ";

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

			static void WriteMessageToConsole(const std::string& msg, const Severity severity = Severity::Info)
			{
				std::cout << GetSeverityStr(severity) << msg << std::endl;
			}

			//TODO: Write function that logs messages to file 
			//ex) write to file at path "$(executable dir)/logs/RenGageAPI.log"
		};
	}
}