#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <rengage.lib/camera/camera.h>
#include <rengage.lib/model/model.h>
#include <rengage.lib/rendering_window.h>
#include <memory>

namespace forest_escape {
	class GameManager;//forward declaration of GameManager class

	const float DEFAULT_FOV_Y = 1.0472f;//in radians
	const float DEFAULT_NEAR_PLANE = 0.1f;
	const float DEFAULT_FAR_PLANE = 1000.0f;

	using ModelPtr = std::unique_ptr<rengage::model::Model>;
	class Renderer
	{
	private:
		float m_fov_y = DEFAULT_FOV_Y;//expressed in radians.
		float m_near_plane_distance = DEFAULT_NEAR_PLANE;
		float m_far_plane_distance = DEFAULT_FAR_PLANE;
		float m_aspect_ratio;
		GLint m_mv_index;
		GLint m_proj_index;
		glm::mat4 m_proj_matrix;
		std::unique_ptr<rengage::camera::Camera> m_camera;
		std::shared_ptr<rengage::OGLInvoker> m_ogl_invoker;

		bool init();
		void update_view_matrix(const glm::vec4& new_position);
		void update_projection_matrix(const float new_aspect_ratio);
		void draw_frame();
		
	public:
		Renderer(std::shared_ptr<rengage::OGLInvoker> ogl_invoker, GLint mv_index, GLint proj_index, float aspect_ratio);
		~Renderer();
		void draw_model(const ModelPtr& model_ptr);
		void set_aspect_ratio(float aspect_ratio);
		friend GameManager;
	};
}

