#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "Logger/Logger.h"

namespace RenGage
{
	const int GL_VERSION_MAJOR = 4;
	const int GL_VERSION_MINOR = 6;
	const int MIN_WINDOW_WIDTH = 800;
	const int MIN_WINDOW_HEIGHT = 800;

	struct WindowAttributes
	{
		std::string name = "";
		int min_width = 800;
		int min_height = 800;
		glm::vec4 rgba = { 0.0f, 0.0f, 0.0f, 1.0f};
		int swap_interval = 1;
	};

	class RenderWindow//TODO: Maybe this class should be decoupled from the core library and be defined in the game itself?
	{
	public:
		RenderWindow(bool fullscreen = true);
		RenderWindow(WindowAttributes, bool fullscreen = false);
		~RenderWindow();

		GLFWwindow* operator()(){ return m_window; }

		inline std::string GetName() const { return m_attributes.name; }
		inline int GetWidth() const { return m_attributes.min_width; }
		inline int GetHeight() const { return m_attributes.min_height; }
		glm::vec4 GetColor() const { return m_attributes.rgba; }
		GLFWwindow* GetGLFWWindow() const { return m_window; }
		void HideWindow() { glfwHideWindow(m_window); }
		void ShowWindow() { glfwShowWindow(m_window); }

	private:
		void Initialize();
		bool CreateDefaultWindow();
		bool CreateCustomWindow();

		Logger m_logger;
		GLFWwindow* m_window;
		bool m_initialized;
		WindowAttributes m_attributes;
		bool m_is_default;
		bool m_start_fullscreen;
	};
}