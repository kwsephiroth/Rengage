#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "logging/logger_macros.h"
#include "logging/ilogger.h"
#include "tools/ogl_invoker.h"

namespace rengage
{
	//namespace//Anonymous namespace restricts variable visibility to this file only.
	//{
	//	int new_window_height = 0;
	//	int new_window_width = 0;
	//}

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

	const int GL_VERSION_MAJOR = 4;//TODO: Determine if version information should be hardcoded or variable.
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
		RenderingWindow(std::shared_ptr<OGLInvoker> oglInvoker, std::shared_ptr<ILogger> logger, WindowAttributes attributes = DEFAULT_WINDOW_ATTRIBS, bool full_screen = false);
		~RenderingWindow();
		GLFWwindow* operator()(){ return m_window; }//TODO: Switch to QT instead of GLFW for window management?
		inline bool initialized() const { return m_initialized; }
		inline std::string name() const { return m_attributes.name; }
		inline int min_width() const { return m_attributes.min_width; }
		inline int min_height() const { return m_attributes.min_height; }
		inline int width() const { return m_width; }
		inline int height() const { return m_height; }
		inline glm::vec4 color() const { return m_attributes.color; }
		inline int swap_interval() const { return m_attributes.swap_interval; }
		inline float aspect_ratio() const { return m_aspect_ratio; }
		inline GLFWwindow* glfw_window() const { return m_window; }
		void hide() { glfwHideWindow(m_window); }
		void show() { glfwShowWindow(m_window); }
		void resize(int new_width, int new_height);

	private:
		void init();
		bool create_default_window();
		bool create_custom_window();

		GLFWwindow* m_window;//TODO: Need a copy/move constructor for this raw pointer member.
		//std::unique_ptr<GLFWwindow> m_window;
		bool m_initialized;
		WindowAttributes m_attributes;
		bool m_is_default;
		bool m_start_fullscreen;
		int m_width;
		int m_height;
		float m_aspect_ratio;
		std::shared_ptr<OGLInvoker> m_ogl_invoker;
		std::shared_ptr<ILogger> m_logger;
	};

	//static void window_resize_callback(GLFWwindow* window, int new_width, int new_height)
	//{
	//	new_window_height = new_height;
	//	new_window_width = new_width;
	//}
}