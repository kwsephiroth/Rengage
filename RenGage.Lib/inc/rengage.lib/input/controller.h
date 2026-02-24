#pragma once
#include <GLFW/glfw3.h>
#include <memory>

namespace rengage::input::controller
{
	enum class ControllerType
	{
		Keyboard,
		Mouse,
		Gamepad
	};

	class Controller
	{
	public:
		virtual ~Controller() = default;
		virtual void enable () = 0;
		virtual void disable() = 0;

	//protected:
		//Controller(std::shared_ptr<GLFWwindow> parentWindow) : m_parent_window(std::move(parentWindow)) {}
		//std::shared_ptr<GLFWwindow> m_parent_window;
	};
}