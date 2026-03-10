#pragma once
#include <GLFW/glfw3.h>
#include <memory>

namespace forest_escape::input
{
	enum class ControllerType
	{
		Keyboard,
		Mouse,
		Gamepad
	};

	class IInputHandler
	{
	public:
		virtual ~IInputHandler() = default;
		virtual void enable () = 0;
		virtual void disable() = 0;

	//protected:
		//Controller(std::shared_ptr<GLFWwindow> parentWindow) : m_parent_window(std::move(parentWindow)) {}
		//std::shared_ptr<GLFWwindow> m_parent_window;
	};
}