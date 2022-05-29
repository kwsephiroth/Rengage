#include <RenderWindow.h>

namespace RenGage
{
	RenderWindow::RenderWindow(bool fullscreen) :
		m_window(nullptr),
		m_initialized(false),
		m_start_fullscreen(fullscreen)
	{
		Initialize();
	}

	RenderWindow::RenderWindow(WindowAttributes attributes, bool fullscreen) :
		m_window(nullptr),
		m_initialized(false), 
		m_attributes(attributes),
		m_start_fullscreen(fullscreen)
	{
		Initialize();
	}

	RenderWindow::~RenderWindow()
	{
		glfwTerminate();
	}

	void RenderWindow::Initialize()
	{
		LOG_INFO(m_logger, "Initializing rendering window.");
		
		if (m_initialized)
		{
			LOG_INFO(m_logger, "Rendering window is already initialized.");
			return;
		}

		if (!glfwInit())
		{
			LOG_ERROR(m_logger, "Failed to initialize the GLFW library.");
			return;
		}

		//Set OpenGL version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);

		//Attempt to create the window
		//m_window = glfwCreateWindow(m_attributes.width, m_attributes.height, m_attributes.name.c_str(), glfwGetPrimaryMonitor(), NULL);
		GLFWmonitor* mainMonitor = nullptr;

		if (m_start_fullscreen)
		{
			mainMonitor = glfwGetPrimaryMonitor();
		}

		//glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);//make initial window invisible
		m_window = glfwCreateWindow(m_attributes.min_width, m_attributes.min_height, m_attributes.name.c_str(), mainMonitor, NULL);
		if (!m_window)
		{
			glfwTerminate();
			LOG_ERROR(m_logger, "Failed to create GLFW window with given context.");
			return;
		}

		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(m_attributes.swap_interval);//Set vsync

		//Must have a valid OpenGL context before initializing glew
		auto errorCode = glewInit();
		if (errorCode != GLEW_OK)
		{
			LOG_ERROR(m_logger, "Failed to initialize GlEW with error code(" + std::to_string(errorCode) + ").");
			return;
		}

		LOG_INFO(m_logger, "GLFW window initialization successful.");
		LOG_INFO(m_logger, "OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)));
		m_initialized = true;
	}

	bool RenderWindow::CreateDefaultWindow()
	{
		return false;
	}

	bool RenderWindow::CreateCustomWindow()
	{
		return false;
	}
}