#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "iinput_handler.h"
#include <rengage.lib/interfaces/iobservable.h>

namespace forest_escape::input
{
	class KeyboardInputHandler : public IInputHandler, public rengage::IObservable
	{
	public:
		KeyboardInputHandler();//std::shared_ptr<GLFWwindow> parentWindow);
		void enable() override;
		void disable() override;
		void add_observer(rengage::IObserver* observer) override;
		void remove_observer(rengage::IObserver* observer) override;
		void handle_key_event(GLFWwindow* window, int key, int scancode, int action, int mods); // Internal method to process keyboard events.
		void handle_char_event(GLFWwindow* window, unsigned int codepoint); // Internal method to process character input events.

	private:
		std::vector<rengage::IObserver*> m_observers;

		void process_key_press(int key);
		//void process_key_release(int key);
		//void process_key_repeat(int key);
	};
}	
