#include <RenderWindow.h>

namespace RenGage
{
	RenderWindow::RenderWindow(const size_t width, const size_t height) :
		m_width(width), m_height(height)
	{
		InitializeWindow();
	}

	void RenderWindow::InitializeWindow()
	{
		//m_logger.LogMsg(LogSeverity::INFO, LogDestination::FILE, "Initializing rendering window");
		LOG_INFO(m_logger, "Initializing rendering window.");
		LOG_WARNING(m_logger, "GLFW window could not be found.");
		LOG_ERROR(m_logger, "Window could not be initialized.");

	}
}