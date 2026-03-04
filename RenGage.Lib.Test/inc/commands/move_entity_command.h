#pragma once
#include "../interfaces/icommand.h"

namespace forest_escape::commands
{
	class MoveEntityCommand : public ICommand
	{
	public:
		MoveEntityCommand() = default;
		void execute() override;
		//void undo() override;
	};
}