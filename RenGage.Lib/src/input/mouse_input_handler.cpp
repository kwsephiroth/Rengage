#include "../../inc/rengage.lib/input/mouse_input_handler.h"
#include "../../inc/rengage.lib/services/logging/logger_macros.h"

namespace rengage::input
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
		std::cout << ("Handling mouse button event: button=" + std::to_string(button) + 
					  ", action=" + std::to_string(action) + 
					  ", mods=" + std::to_string(mods)) << std::endl;
	}

	void MouseInputHandler::handle_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		std::cout << ("Handling mouse scroll event: xoffset=" + std::to_string(xoffset) + 
					  ", yoffset=" + std::to_string(yoffset)) << std::endl;
	}
}