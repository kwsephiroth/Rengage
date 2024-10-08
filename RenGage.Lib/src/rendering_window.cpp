#include "../inc/rengage.lib/rendering_window.h"

namespace rengage
{
	RenderingWindow::RenderingWindow(std::shared_ptr<OGLInvoker> ogl_invoker, std::shared_ptr<ILogger> logger, WindowAttributes attributes, bool full_screen) :
		m_window(nullptr),
		m_initialized(false), 
		m_attributes(attributes),
		m_start_fullscreen(full_screen),
		m_width(attributes.min_width),
		m_height(attributes.min_height),
		m_ogl_invoker(std::move(ogl_invoker)),
		m_logger(std::move(logger))
	{
		init();
	}

	RenderingWindow::~RenderingWindow()
	{
		glfwTerminate();
	}

	void RenderingWindow::init()
	{
		LOG_INFO(m_logger, "Initializing rendering window.");

		if (m_width <= 0 || m_height <= 0)
		{
			LOG_ERROR(m_logger, "Invalid window width and/or height.");
		}

		m_aspect_ratio = (float)m_width / (float)m_height;
		
		if (m_initialized) {
			LOG_INFO(m_logger, "Rendering window is already initialized.");
			return;
		}

		if (!glfwInit()) {
			LOG_ERROR(m_logger, "Failed to initialize the GLFW library.");
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
			LOG_ERROR(m_logger, "Failed to create GLFW window with given context.");
			return;
		}
		//glfwMakeContextCurrent(m_window);
		//glfwSwapInterval(m_attributes.swap_interval);//Set vsync
		LOG_INFO(m_logger, "GLFW window initialization successful.");
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

	void RenderingWindow::resize(int new_width, int new_height)
	{
		if (new_width < 1) {
			LOG_ERROR(m_logger, "Invalid window width.");
			return;
		}

		if (new_height < 1) {
			LOG_ERROR(m_logger, "Invalid window height");
			return;
		}

		m_width = new_width;
		m_height = new_height;
		m_aspect_ratio = (float)m_width / (float)m_height;
		std::stringstream ss;
		ss << "\nWindow Resized!"
		   << "\nNew Width: " + std::to_string(m_width)
		   << "\nNew Height: " + std::to_string(m_height)
		   << "\nNew Aspect Ratio: " + std::to_string(m_aspect_ratio) << "\n";
		LOG_INFO(m_logger, ss.str());
	}
}