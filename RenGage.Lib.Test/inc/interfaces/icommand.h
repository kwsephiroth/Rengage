#pragma once

namespace forest_escape::commands
{
	class ICommand
	{
	public:
		virtual ~ICommand() = default;
		virtual void execute() = 0;
		//virtual void undo() = 0;
	};
}