#pragma once
#include <unordered_map>
#include <memory>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <rengage.lib/services/logging/logger_macros.h>
#include <rengage.lib/services/logging/file_logger.h>
#include <rengage.lib/services/logging/console_logger.h>
//#include <rengage.lib/tools/opengl_invoke.h>
#include <rengage.lib/rendering_window.h>
#include <rengage.lib/shader/shader_program.h>
#include <rengage.lib/model/model.h>
#include <rengage.lib/model/model_factory.h>
#include <rengage.lib/camera/camera.h>
#include <rengage.lib/services/service_locator.h>
#include "input/keyboard_input_handler.h"
#include "input/mouse_input_handler.h"
#include "renderer.h"

namespace forest_escape {

	using ModelPtr = std::unique_ptr<rengage::model::Model>;
	class GameManager
	{
	private:
		using ModelMap = std::unordered_map<std::string, ModelPtr>;
		std::unique_ptr<rengage::RenderingWindow> m_window;
		std::unique_ptr<rengage::shader::ShaderProgram> m_program;
		std::unique_ptr<Renderer> m_renderer;
		std::shared_ptr<rengage::OGLInvoker> m_ogl_invoker;
		GLuint m_program_id;
		ModelMap m_models;
		bool m_game_loop_started = false;
		bool m_initialized = false;
		std::unique_ptr<input::KeyboardInputHandler> m_keyboard_input_handler;
		std::unique_ptr<input::MouseInputHandler> m_mouse_input_handler;

		void init();
		bool init_window();
		bool init_renderer();
		bool init_shader_program();
		bool init_models();
		//bool init_controller();
		bool init_uniform_indices();
		bool program_is_valid();
		void draw_model(const ModelPtr& model_ptr);
		void draw_frame();

	public:
		GameManager();
		~GameManager();
		void start_game_loop();
		void on_window_resize(GLFWwindow*, int, int);
	};
}

