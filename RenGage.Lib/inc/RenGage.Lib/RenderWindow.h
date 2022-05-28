#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger/Logger.h"

namespace RenGage
{
	class RenderWindow
	{
	public:
		RenderWindow(const size_t width, const size_t height);
		~RenderWindow() = default;

		inline size_t GetWidth() const { return m_width; }
		inline size_t GetHeight() const { return m_height; }

	private:
		void InitializeWindow();

		Logger m_logger;
		size_t m_width;
		size_t m_height;
	};
}