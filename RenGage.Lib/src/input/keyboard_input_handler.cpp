#include "../../inc/rengage.lib/input/keyboard_input_handler.h"
#include "../../inc/rengage.lib/services/logging/logger_macros.h"

namespace rengage::input
{
	KeyboardInputHandler::KeyboardInputHandler()///std::shared_ptr<GLFWwindow> parentWindow) 
		//: Controller(std::move(parentWindow))
	{
	}

	void KeyboardInputHandler::enable()
	{
	}
	void KeyboardInputHandler::disable()
	{
	}

	void KeyboardInputHandler::handle_key_event(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		std::cout << ("Handling key event: key=" + std::to_string(key) + 
					  ", scancode=" + std::to_string(scancode) + 
					  ", action=" + std::to_string(action) + 
					  ", mods=" + std::to_string(mods)) << std::endl;
	}

	void KeyboardInputHandler::handle_char_event(GLFWwindow* window, unsigned int codepoint)
	{
		std::cout << ("Handling char event: codepoint=" + std::to_string(codepoint)) << std::endl;
	}
}