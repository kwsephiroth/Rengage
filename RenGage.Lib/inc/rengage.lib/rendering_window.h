#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "services/logging/logger_macros.h"
#include "interfaces/ilogger.h"
#include "tools/ogl_invoker.h"
#include <functional>

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

	// Event handler type aliases
	using ResizeHandler = std::function<void(GLFWwindow*, int, int)>;
	using KeyEventHandler = std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>;
	using CharEventHandler = std::function<void(GLFWwindow* window, unsigned int codepoint)>;
	using MouseMovementHandler = std::function<void(GLFWwindow* window, double xpos, double ypos)>;
	using MouseButtonHandler = std::function<void(GLFWwindow* window, int button, int action, int mods)>;
	using MouseScrollHandler = std::function<void(GLFWwindow* window, double xoffset, double yoffset)>;

	class RenderingWindow//TODO: Maybe this class should be decoupled from the core library and be defined in the game itself?
	{
	public:
		RenderingWindow(std::shared_ptr<OGLInvoker> ogl_invoker, WindowAttributes attributes = DEFAULT_WINDOW_ATTRIBS, bool full_screen = false);
		~RenderingWindow();
		GLFWwindow* operator()() { return m_window; }//TODO: Switch to QT instead of GLFW for window management?
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

		//Event handler registration methods
		void register_resize_handler(ResizeHandler handler);
		void register_key_event_handler(KeyEventHandler handler);
		void register_char_event_handler(CharEventHandler handler);
		void register_mouse_movement_handler(MouseMovementHandler handler);
		void register_mouse_button_handler(MouseButtonHandler handler);
		void register_mouse_scroll_handler(MouseScrollHandler handler);

	private:
		class EventHandler //: public Observable //TODO
		{
		public:
			EventHandler(GLFWwindow* window) :
				m_window(window)
			{
			}
			void register_handlers();

			ResizeHandler m_resize_handler;
			KeyEventHandler m_key_event_handler;
			CharEventHandler m_char_event_handler;
			MouseMovementHandler m_mouse_movement_handler;
			MouseButtonHandler m_mouse_button_handler;
			MouseScrollHandler m_mouse_scroll_handler;

			void on_key_event(GLFWwindow* window, int key, int scancode, int action, int mods);
			void on_char_event(GLFWwindow* window, unsigned int codepoint);
			void on_window_resize(GLFWwindow* window, int new_width, int new_height);
			void on_mouse_movement(GLFWwindow* window, double xpos, double ypos);
			void on_mouse_button(GLFWwindow* window, int button, int action, int mods);
			void on_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);
		private:
			GLFWwindow* m_window = nullptr;
		};

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
		std::unique_ptr<EventHandler> m_event_handler;
	};

	//static void window_resize_callback(GLFWwindow* window, int new_width, int new_height)
	//{
	//	new_window_height = new_height;
	//	new_window_width = new_width;
	//}
}