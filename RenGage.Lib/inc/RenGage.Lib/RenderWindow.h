#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "Logger/Logger.h"

namespace RenGage
{
	const int GL_VERSION_MAJOR = 4;
	const int GL_VERSION_MINOR = 6;

	struct WindowAttributes
	{
		std::string name = "";
		int width = 0;
		int height = 0;
		glm::vec3 rgb_color = { 0.0f, 0.0f, 0.0f };
		int swap_interval = 1;
	};

	class RenderWindow//TODO: Maybe this class should be decoupled from the core library and be defined in the game itself?
	{
	public:
		RenderWindow();
		RenderWindow(WindowAttributes);
		~RenderWindow();

		inline int GetWidth() const { return m_attributes.width; }
		inline int GetHeight() const { return m_attributes.height; }

	private:
		void InitializeWindow();
		bool CreateDefaultWindow();
		bool CreateCustomWindow();

		Logger m_logger;
		GLFWwindow* m_window;
		bool m_initialized;
		WindowAttributes m_attributes;
		bool m_is_default;
	};
}