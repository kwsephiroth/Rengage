#include "../../inc/rengage.lib/input/keyboard_controller.h"
#include "../../inc/rengage.lib/services/logging/logger_macros.h"

namespace rengage::input::controller
{
	KeyboardController::KeyboardController(std::shared_ptr<GLFWwindow> parentWindow) 
		: Controller(std::move(parentWindow))
	{
	}

	void KeyboardController::enable()
	{
		LOG_INFO("Enabling keyboard controller.");
		//glfwSetKeyCallback(m_parent_window.get(), handle_key_event);
		//glfwSetCharCallback(m_parent_window.get(), handle_char_event);
	}
	void KeyboardController::disable()
	{
		LOG_INFO("Disabling keyboard controller.");
		glfwSetKeyCallback(m_parent_window.get(), nullptr);
		glfwSetCharCallback(m_parent_window.get(), nullptr);
	}

	void KeyboardController::handle_key_event(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		LOG_DEBUG("Handling key event: key=" + std::to_string(key) + ", scancode=" + std::to_string(scancode) + ", action=" + std::to_string(action) + ", mods=" + std::to_string(mods));
	}

	void KeyboardController::handle_char_event(GLFWwindow* window, unsigned int codepoint)
	{
		LOG_DEBUG("Handling char event: codepoint=" + std::to_string(codepoint));
	}
}