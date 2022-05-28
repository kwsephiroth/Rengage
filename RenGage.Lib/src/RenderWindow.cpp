#include <RenderWindow.h>

namespace RenGage
{
	RenderWindow::RenderWindow()
	{
		InitializeWindow();
	}

	RenderWindow::RenderWindow(WindowAttributes attributes) :
		m_window(nullptr),
		m_initialized(false), 
		m_attributes(attributes)
	{
		InitializeWindow();
	}

	RenderWindow::~RenderWindow()
	{
		glfwTerminate();
	}

	void RenderWindow::InitializeWindow()
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
		m_window = glfwCreateWindow(m_attributes.width, m_attributes.height, m_attributes.name.c_str(), NULL, NULL);
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