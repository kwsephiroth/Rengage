#include <rengage.lib/services/logging/logger_macros.h>
#include "../../inc/input/keyboard_input_handler.h"

namespace forest_escape::input
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
		//std::cout << ("Handling key event: key=" + std::to_string(key) + 
		//			  ", scancode=" + std::to_string(scancode) + 
		//			  ", action=" + std::to_string(action) + 
		//			  ", mods=" + std::to_string(mods)) << std::endl;
		switch (action)
		{
			case GLFW_PRESS:
			{
				process_key_press(key);
			}
			break;

			case GLFW_RELEASE:
			{
			}
			break;

			case GLFW_REPEAT:
			{
			}
			break;
		}
	}

	void KeyboardInputHandler::handle_char_event(GLFWwindow* window, unsigned int codepoint)
	{
		//std::cout << ("Handling char event: codepoint=" + std::to_string(codepoint)) << std::endl;
	}

	void KeyboardInputHandler::process_key_press(int key)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
			{
				std::cout << "Escape key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_W:
			{
				std::cout << "W key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_A:
			{
				std::cout << "A key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_S:
			{
				std::cout << "S key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_D:
			{
				std::cout << "D key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_SPACE:
			{
				std::cout << "Space key pressed." << std::endl;
			}
			break;

			//case GLFW_KEY_UP:
			//{
			//	std::cout << "Up arrow key pressed." << std::endl;
			//}
			//break;

			//case GLFW_KEY_DOWN:
			//{
			//	std::cout << "Down arrow key pressed." << std::endl;
			//}
			//break;

			//case GLFW_KEY_LEFT:
			//{
			//	std::cout << "Left arrow key pressed." << std::endl;
			//}
			//break;

			//case GLFW_KEY_RIGHT:
			//{
			//	std::cout << "Right arrow key pressed." << std::endl;
			//}
			//break;
		}
	}
}