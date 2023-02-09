#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "logger/logger_macros.h"

namespace rengage
{
	const int GL_VERSION_MAJOR = 4;
	const int GL_VERSION_MINOR = 6;
	const int MIN_WINDOW_WIDTH = 800;
	const int MIN_WINDOW_HEIGHT = 800;

	struct window_attributes
	{
		std::string name = "";
		int min_width = 800;
		int min_height = 800;
		glm::vec4 rgba = { 0.0f, 0.0f, 0.0f, 1.0f};
		int swap_interval = 1;
	};

	using glfw_window = GLFWwindow;
	using glfw_monitor = GLFWmonitor;

	class rendering_window//TODO: Maybe this class should be decoupled from the core library and be defined in the game itself?
	{
	public:
		rendering_window(bool full_screen = true);
		rendering_window(window_attributes, bool full_screen = false);
		~rendering_window();

		glfw_window* operator()(){ return m_window; }

		inline std::string get_name() const { return m_attributes.name; }
		inline int get_width() const { return m_attributes.min_width; }
		inline int get_height() const { return m_attributes.min_height; }
		glm::vec4 get_color() const { return m_attributes.rgba; }
		glfw_window* get_glfw_window() const { return m_window; }
		void hide_window() { glfwHideWindow(m_window); }
		void show_window() { glfwShowWindow(m_window); }

	private:
		void init();
		bool create_default_window();
		bool create_custom_window();

		glfw_window* m_window;
		bool m_initialized;
		window_attributes m_attributes;
		bool m_is_default;
		bool m_start_fullscreen;
	};
}