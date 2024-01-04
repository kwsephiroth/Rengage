#include "../inc/rengage.lib/rendering_window.h"

namespace rengage
{
	RenderingWindow::RenderingWindow(WindowAttributes attributes, bool full_screen) :
		m_window(nullptr),
		m_initialized(false), 
		m_attributes(attributes),
		m_start_fullscreen(full_screen)
	{
		init();
	}

	RenderingWindow::~RenderingWindow()
	{
		glfwTerminate();
	}

	void RenderingWindow::init()
	{
		LOG_INFO("Initializing rendering window.");
		
		if (m_initialized) {
			LOG_INFO("Rendering window is already initialized.");
			return;
		}

		if (!glfwInit()) {
			LOG_ERROR("Failed to initialize the GLFW library.");
			return;
		}

		//Set OpenGL version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
		
		//Attempt to create the window
		GLFWmonitor* main_monitor = nullptr;

		if (m_start_fullscreen) {
			main_monitor = glfwGetPrimaryMonitor();
		}

		m_window = glfwCreateWindow(m_attributes.min_width, m_attributes.min_height, m_attributes.name.c_str(), main_monitor, NULL);
		//m_window = glfwCreateWindow(m_attributes.min_width, m_attributes.min_height, m_attributes.name.c_str(), main_monitor, NULL);
		if (!m_window) {
			glfwTerminate();
			LOG_ERROR("Failed to create GLFW window with given context.");
			return;
		}
		//glfwMakeContextCurrent(m_window);
		//glfwSwapInterval(m_attributes.swap_interval);//Set vsync
		LOG_INFO("GLFW window initialization successful.");
		m_initialized = true;
	}

	bool RenderingWindow::create_default_window()
	{
		return false;
	}

	bool RenderingWindow::create_custom_window()
	{
		return false;
	}
}