#pragma once
#include <GLFW/glfw3.h>

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
	};
}