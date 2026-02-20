#include "../../inc/rengage.lib/input/keyboard_controller.h"
#include "../../inc/rengage.lib/services/logging/logger_macros.h"

namespace rengage::input::controller
{
	void KeyboardController::enable()
	{
		LOG_INFO("Enabling keyboard controller.");
	}
	void KeyboardController::disable()
	{
		LOG_INFO("Disabling keyboard controller.");
	}
}