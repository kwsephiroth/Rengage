#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "input_handler.h"

namespace forest_escape::input
{
	class MouseInputHandler : public InputHandler
	{
	public:
		MouseInputHandler();//std::shared_ptr<GLFWwindow> parentWindow);
		void enable() override;
		void disable() override;

		void handle_mouse_movement(GLFWwindow* window, double xpos, double ypos);
		void handle_mouse_button(GLFWwindow* window, int button, int action, int mods);
		void handle_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);
	private:
	};
}