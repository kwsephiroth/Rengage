#pragma once
#include "controller.h"

namespace rengage::input::controller
{
	class KeyboardController : public Controller
	{
	public:
		KeyboardController() = default;
		void enable() override; // Handles registering of keyboard input callbacks and any other necessary setup for keyboard input.
		void disable() override; // Handles unregistering of keyboard input callbacks and any other necessary teardown for keyboard input.
	};
}	
