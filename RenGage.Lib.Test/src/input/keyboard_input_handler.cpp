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

	void KeyboardInputHandler::add_observer(rengage::IObserver* observer)
	{
		m_observers.push_back(observer);
	}

	void KeyboardInputHandler::remove_observer(rengage::IObserver* observer)
	{
		m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
	}

	void KeyboardInputHandler::handle_key_event(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//std::cout << ("Handling key event: key=" + std::to_string(key) + 
		//			  ", scancode=" + std::to_string(scancode) + 
		//			  ", action=" + std::to_string(action) + 
		//			  ", mods=" + std::to_string(mods)) << std::endl;
		auto event_type = rengage::EventType::Undefined;
		switch (action)
		{
			case GLFW_PRESS:
			{
				event_type = rengage::EventType::KeyPressed;
				//process_key_press(key);
			}
			break;

			case GLFW_RELEASE:
			{
				event_type = rengage::EventType::KeyReleased;
				//process_key_release(key);
			}
			break;

			case GLFW_REPEAT:
			{
				event_type = rengage::EventType::KeyRepeated;
				//process_key_repeat(key);
			}
			break;
		}
		if (event_type != rengage::EventType::Undefined)
		{
			for (auto observer : m_observers)
			{
				observer->on_notify(event_type, key);
			}
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
				//std::cout << "Escape key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_W:
			{
				//std::cout << "W key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_A:
			{
				//std::cout << "A key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_S:
			{
				//std::cout << "S key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_D:
			{
				//std::cout << "D key pressed." << std::endl;
			}
			break;

			case GLFW_KEY_SPACE:
			{
				//std::cout << "Space key pressed." << std::endl;
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