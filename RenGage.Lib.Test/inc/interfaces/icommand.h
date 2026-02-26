#pragma once

namespace MyNamespace
{
	class ICommand
	{
	public:
		virtual ~ICommand() = default;
		virtual void execute() = 0;
	};
}