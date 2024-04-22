#pragma once
#include <unordered_map>
#include <memory>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <rengage.lib/logging/logger_macros.h>
#include <rengage.lib/tools/opengl_invoke.h>
#include <rengage.lib/rendering_window.h>
#include <rengage.lib/shader/shader_program.h>
#include <rengage.lib/model/model.h>
#include <rengage.lib/model/model_factory.h>
#include <rengage.lib/camera/camera.h>
#include "renderer.h"

namespace forest_escape {
	class GameManager//TODO: Determine if this should be a Singleton.
	{
	private:
		using ModelMap = std::unordered_map<std::string, std::unique_ptr<rengage::model::Model>>;
		std::unique_ptr<rengage::RenderingWindow> m_window;
		std::unique_ptr<rengage::shader::ShaderProgram> m_program;
		std::unique_ptr<Renderer> m_renderer;
		GLuint m_program_id;
		ModelMap m_models;
		bool m_game_loop_started = false;

		void init();
		bool init_window();
		bool init_renderer();
		bool init_shader_program();
		bool init_models();
		//bool init_controller();
		bool init_uniform_indices();
		bool program_is_valid();
		void draw_model(const std::unique_ptr<rengage::model::Model>&);
		void draw_frame();

	public:
		GameManager();
		~GameManager();
		void start_game_loop();
		void on_window_resize(GLFWwindow*, int, int);
	};
}

