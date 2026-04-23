#include "../inc/renderer.h"
#include "../../RenGage.Lib/inc/rengage.lib/model/vertex.h"

namespace forest_escape {
	Renderer::Renderer(GLint mv_index, GLint proj_index, float aspect_ratio) :
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
		auto ogl_invoker = rengage::services::ServiceLocator::get_service<rengage::services::OGLInvoker>();
		ogl_invoker->invoke(glUniformMatrix4fv, ARGS(m_proj_index, 1, GL_FALSE, glm::value_ptr(m_proj_matrix)));
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

		auto model_view_matrix =  m_camera->view_matrix() * model_ptr->model_matrix();
		static auto ogl_invoker = rengage::services::ServiceLocator::get_service<rengage::services::OGLInvoker>();
		ogl_invoker->invoke(glUniformMatrix4fv, ARGS(m_mv_index, 1, GL_FALSE, glm::value_ptr(model_view_matrix)));

		//Draw each mesh of the model.
		ogl_invoker->invoke(glBindVertexArray, ARGS(model_ptr->VAO().value()));
		for (const auto& mesh : model_ptr->meshes())
		{	
			//ogl_invoker->invoke(glBindVertexArray, ARGS(mesh.VAO().value()));
			//if (const auto& textures = mesh.Textures(); !textures.empty())//TODO: Figure out why there can be more than one texture per mesh.
			//{
			//	//ogl_invoker->invoke(glActiveTexture, ARGS(GL_TEXTURE0));
			//	ogl_invoker->invoke(glBindTexture, ARGS(GL_TEXTURE_2D, mesh.Textures()[0]->handle()));
			//}
			//ogl_invoker->invoke(glBindBuffer, ARGS(GL_ARRAY_BUFFER, mesh.VBO().value()));
			//ogl_invoker->invoke(glEnableVertexAttribArray, ARGS(model_ptr->position_index().value()));
			//ogl_invoker->invoke(glVertexAttribPointer, ARGS(model_ptr->position_index().value(), 3, GL_FLOAT, false, sizeof(rengage::model::Vertex), (GLvoid*)0));
			//ogl_invoker->invoke(glBindBuffer, ARGS(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO().value()));
			mesh.bind();
			ogl_invoker->invoke(glDrawElements, ARGS(GL_TRIANGLES, mesh.indices().size(), GL_UNSIGNED_INT, nullptr));
			//ogl_invoker->invoke(glBindVertexArray, ARGS(0));
		}
		ogl_invoker->invoke(glBindVertexArray, ARGS(0));
	}
}
