#include "../inc/renderer.h"

namespace forest_escape {
	Renderer::Renderer(std::shared_ptr<rengage::OGLInvoker> ogl_invoker, GLint mv_index, GLint proj_index, float aspect_ratio) :
		m_ogl_invoker(ogl_invoker),
		m_mv_index(mv_index),
		m_proj_index(proj_index),
		m_aspect_ratio(aspect_ratio)
	{
		init();
	}

	Renderer::~Renderer()
	{

	}

	bool Renderer::init()
	{
		update_projection_matrix(m_aspect_ratio);
		m_camera = std::make_unique<rengage::camera::Camera>();
		return true;
	}

	void Renderer::set_aspect_ratio(float aspect_ratio)
	{
		m_aspect_ratio = aspect_ratio;
		update_projection_matrix(aspect_ratio);
	}

	void Renderer::update_view_matrix(const glm::vec4& new_position)
	{

	}

	void Renderer::update_projection_matrix(const float new_aspect_ratio)
	{
		m_proj_matrix = glm::perspective(m_fov_y, new_aspect_ratio, m_near_plane_distance, m_far_plane_distance);
		m_ogl_invoker->invoke(glUniformMatrix4fv, ARGS(m_proj_index, 1, GL_FALSE, glm::value_ptr(m_proj_matrix)));
	}

	void Renderer::draw_frame()
	{

	}

	void Renderer::draw_model(const ModelPtr& model_ptr)
	{
		//TODO: create model-view matrix here.
		if (!model_ptr || !model_ptr->initialized())
		{
			return;
			//TODO: Log error then return.
		}

		auto model_view_matrix = m_camera->view_matrix() * model_ptr->model_matrix();
		m_ogl_invoker->invoke(glUniformMatrix4fv, ARGS(m_mv_index, 1, GL_FALSE, glm::value_ptr(model_view_matrix)));
		//opengl_invoke(glBindVertexArray, ARGS(model_ptr->VAO().value()));
		//std::cout << "model view matrix = " << glm::to_string(model_view_matrix) << "\n";
		//std::cout << "perspective matrix = " << glm::to_string(m_proj_matrix) << "\n";

		//Draw each mesh of the model.
		for (const auto& mesh : model_ptr->meshes())
		{
			m_ogl_invoker->invoke(glBindVertexArray, ARGS(mesh.VAO().value()));
			//opengl_invoke(glBindBuffer, ARGS(GL_ARRAY_BUFFER, mesh.VBO().value()));
			//opengl_invoke(glVertexAttribPointer, ARGS(0, 3, GL_FLOAT, false, sizeof(rengage::model::Vertex), (GLvoid*)0));
			//opengl_invoke(glBindBuffer, ARGS(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO().value()));
			m_ogl_invoker->invoke(glDrawElements, ARGS(GL_TRIANGLES, mesh.indices().size(), GL_UNSIGNED_INT, nullptr));
			//opengl_invoke(glDrawArrays, ARGS(GL_TRIANGLES, 0, mesh.total_vertices()));
		}
		//opengl_invoke(glBindVertexArray, ARGS(0));
	}
}
