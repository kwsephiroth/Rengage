#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "logger/logger_macros.h"

namespace rengage
{
	struct Resolution
	{
		unsigned int horizontal;
		unsigned int vertical;
	};

	struct WindowAttributes
	{
		std::string name;
		int min_width;
		int min_height;
		glm::vec4 color;
		int swap_interval;
	};

	const int GL_VERSION_MAJOR = 4;
	const int GL_VERSION_MINOR = 6;
	const int MIN_WINDOW_WIDTH = 800;
	const int MIN_WINDOW_HEIGHT = 800;
	const Resolution RES_1080P{ 1920, 1080 };
	const Resolution RES_1440P{ 2560, 1440 };
	const Resolution RES_2160P{ 3840, 2160 };
	const Resolution RES_2K = RES_1440P;
	const Resolution RES_4k = RES_2160P;
	const glm::vec4 DEFAULT_WINDOW_COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };
	const unsigned int DEFAULT_SWAP_INTERVAL = 1;
	const std::string DEFAULT_WINDOW_NAME = "";
	const WindowAttributes DEFAULT_WINDOW_ATTRIBS{ DEFAULT_WINDOW_NAME, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT, DEFAULT_WINDOW_COLOR, DEFAULT_SWAP_INTERVAL };

	class RenderingWindow//TODO: Maybe this class should be decoupled from the core library and be defined in the game itself?
	{
	public:
		explicit RenderingWindow(WindowAttributes attributes = DEFAULT_WINDOW_ATTRIBS, bool full_screen = false);
		~RenderingWindow();
		GLFWwindow* operator()(){ return m_window; }//TODO: Switch to QT instead of GLFW for window management?
		inline std::string name() const { return m_attributes.name; }
		inline int width() const { return m_attributes.min_width; }
		inline int height() const { return m_attributes.min_height; }
		inline glm::vec4 color() const { return m_attributes.color; }
		inline GLFWwindow* glfw_window() const { return m_window; }
		void hide_window() { glfwHideWindow(m_window); }
		void show_window() { glfwShowWindow(m_window); }

	private:
		void init();
		bool create_default_window();
		bool create_custom_window();

		GLFWwindow* m_window;
		bool m_initialized;
		WindowAttributes m_attributes;
		bool m_is_default;
		bool m_start_fullscreen;
	};
}