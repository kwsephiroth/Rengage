#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "input_handler.h"

namespace forest_escape::input
{
	class KeyboardInputHandler : public InputHandler
	{
	public:
		KeyboardInputHandler();//std::shared_ptr<GLFWwindow> parentWindow);
		void enable() override;
		void disable() override;
		
		void handle_key_event(GLFWwindow* window, int key, int scancode, int action, int mods); // Internal method to process keyboard events.
		void handle_char_event(GLFWwindow* window, unsigned int codepoint); // Internal method to process character input events.
	
	private:
		void process_key_press(int key);
		//void process_key_release(int key);
		//void process_key_repeat(int key);
	};
}	
