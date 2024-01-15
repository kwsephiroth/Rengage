#pragma once
#include <unordered_map>
#include <memory>
#include <glm/vec2.hpp>
#include <rengage.lib/logging/logger_macros.h>
#include <rengage.lib/tools/opengl_invoke.h>
#include <rengage.lib/rendering_window.h>
#include <rengage.lib/shader/shader_program.h>
#include <rengage.lib/model/model.h>
#include <rengage.lib/model/model_factory.h>
#include <rengage.lib/camera/camera.h>

namespace forest_escape {
	class GameManager//TODO: Determine if this should be a Singleton.
	{
		using ModelMap = std::unordered_map<std::string, std::unique_ptr<rengage::model::Model>>;

	private:
		std::unique_ptr<rengage::RenderingWindow> m_window;
		std::unique_ptr<rengage::shader::ShaderProgram> m_shader_program;
		ModelMap m_models;

		void init();
		bool init_window();
		bool init_shader_program();
		bool init_models();
		//bool init_controller();
		void draw_model(const std::unique_ptr<rengage::model::Model>&);

	public:
		GameManager();
		~GameManager();
		void start_game_loop();
	};
}

