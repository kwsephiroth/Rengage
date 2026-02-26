#include <rengage.lib/services/logging/logger_macros.h>
#include "../../inc/input/mouse_input_handler.h"

namespace forest_escape::input
{
	MouseInputHandler::MouseInputHandler()///std::shared_ptr<GLFWwindow> parentWindow) 
		//: Controller(std::move(parentWindow))
	{
	}

	void MouseInputHandler::enable()
	{
	}

	void MouseInputHandler::disable()
	{
	}

	void MouseInputHandler::handle_mouse_movement(GLFWwindow* window, double xpos, double ypos)
	{
		std::cout << ("Handling mouse movement event: xpos=" + std::to_string(xpos) + 
					  ", ypos=" + std::to_string(ypos)) << std::endl;
	}

	void MouseInputHandler::handle_mouse_button(GLFWwindow* window, int button, int action, int mods)
	{
		////std::cout << ("Handling mouse button event: button=" + std::to_string(button) + 
		////			  ", action=" + std::to_string(action) + 
		////			  ", mods=" + std::to_string(mods)) << std::endl;
		switch (action)
		{
			case GLFW_PRESS:
			{
				process_button_press(button);
			}
			break;

			case GLFW_RELEASE:
			{
			}
			break;
		}
	}

	void MouseInputHandler::handle_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		std::cout << ("Handling mouse scroll event: xoffset=" + std::to_string(xoffset) + 
					  ", yoffset=" + std::to_string(yoffset)) << std::endl;
	}

	void MouseInputHandler::process_mouse_movement(double xpos, double ypos)
	{
	}

	void MouseInputHandler::process_button_press(int button)
	{
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
			{
				std::cout << "Left mouse button pressed." << std::endl;
			}
			break;
			case GLFW_MOUSE_BUTTON_RIGHT:
			{
				std::cout << "Right mouse button pressed." << std::endl;
			}
			break;
			case GLFW_MOUSE_BUTTON_MIDDLE:
			{
				std::cout << "Middle mouse button pressed." << std::endl;
			}
			break;
		}
	}

	void MouseInputHandler::process_mouse_scroll(double xoffset, double yoffset)
	{
	}
}