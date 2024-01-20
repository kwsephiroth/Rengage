#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <rengage.lib/camera/camera.h>
#include <rengage.lib/model/model.h>
#include <rengage.lib/rendering_window.h>
#include <memory>

namespace forest_escape {
	class GameManager;//forward declaration of GameManager class

	class Renderer
	{
	private:
		glm::mat4 m_proj_matrix;
		glm::mat4 m_view_matrix;

		bool init();
		bool init_projection_matrix();
		bool init_view_matrix();
		void update_view_matrix(const glm::vec4& new_position);
		void draw_frame();
		void draw_model(const std::unique_ptr<rengage::model::Model>& model_ptr);

	public:
		Renderer();
		~Renderer();
		friend GameManager;
	};
}

