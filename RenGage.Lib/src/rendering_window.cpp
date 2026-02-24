#include "../inc/rengage.lib/rendering_window.h"

namespace rengage
{

#define WINDOW_CALLBACK(function_name)\
	[](GLFWwindow* window, auto... args) {\
		auto pointer = static_cast<RenderingWindow::EventHandler*>(glfwGetWindowUserPointer(window));\
		if(pointer) pointer->function_name(window, args...);\
	}

	RenderingWindow::RenderingWindow(std::shared_ptr<OGLInvoker> ogl_invoker, WindowAttributes attributes, bool full_screen) :
		m_window(nullptr),
		m_initialized(false),
		m_attributes(attributes),
		m_start_fullscreen(full_screen),
		m_width(attributes.min_width),
		m_height(attributes.min_height),
		m_ogl_invoker(std::move(ogl_invoker))
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

		if (m_width <= 0 || m_height <= 0)
		{
			LOG_ERROR("Invalid window width and/or height.");
		}

		m_aspect_ratio = (float)m_width / (float)m_height;

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

		// Setup event handlers for window events.
		m_event_handler = std::make_unique<EventHandler>(m_window);
		m_event_handler->register_handlers();

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

	void RenderingWindow::resize(int new_width, int new_height)
	{
		if (new_width < 1) {
			LOG_ERROR("Invalid window width.");
			return;
		}

		if (new_height < 1) {
			LOG_ERROR("Invalid window height");
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
		//LOG_INFO(ss.str());
		std::cout << ss.str() << std::endl;
	}

	void RenderingWindow::EventHandler::register_handlers()
	{
		glfwSetWindowUserPointer(m_window, this);//Enables GLFW to use our EventHandler instance for callback invocation.
		glfwSetWindowSizeCallback(m_window, WINDOW_CALLBACK(on_window_resize));
		glfwSetKeyCallback(m_window, WINDOW_CALLBACK(on_key_event));
	}

	void RenderingWindow::set_resize_handler(ResizeHandler handler)
	{
		m_event_handler->m_resize_handler = std::move(handler);
	}

	void RenderingWindow::set_key_event_handler(KeyEventHandler handler)
	{
		m_event_handler->m_key_event_handler = std::move(handler);
	}

	void RenderingWindow::EventHandler::on_window_resize(GLFWwindow* window, int new_width, int new_height)
	{
		if (m_resize_handler) {
			m_resize_handler(window, new_width, new_height);
		}
		else {
			LOG_WARNING("No resize handler registered for window resize event.");
		}
	}

	void RenderingWindow::EventHandler::on_key_event(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (m_key_event_handler) {
			m_key_event_handler(window, key, scancode, action, mods);
		}
		else {
			LOG_WARNING("No key event handler registered for key event.");
		}
	}
}