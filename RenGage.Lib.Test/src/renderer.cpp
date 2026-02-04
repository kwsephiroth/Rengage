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

		// TODO: Move tree to better position.
		//static glm::mat4 tempModelMatrix = glm::mat4(1.0f);//Initialize to identity matrix
		//tempModelMatrix = glm::translate(tempModelMatrix, glm::vec3(-0.5f, 0.1f, depthOffset));
		//glm::vec3 euler_angles(glm::radians(xRotAngle), glm::radians(-yRotAngle), 0);
		//glm::quat my_quat = glm::quat(euler_angles);
		//tempModelMatrix *= glm::toMat4(my_quat);
		//tempModelMatrix = glm::scale(tempModelMatrix, glm::vec3(.3f, .3f, .3f));
		//auto vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -0.1f, -(cameraZ + depthOffset)));

		auto model_view_matrix = m_camera->view_matrix() * model_ptr->model_matrix();
		m_ogl_invoker->invoke(glUniformMatrix4fv, ARGS(m_mv_index, 1, GL_FALSE, glm::value_ptr(model_view_matrix)));
		//m_ogl_invoker->invoke(glBindVertexArray, ARGS(model_ptr->VAO().value()));
		//std::cout << "model view matrix = " << glm::to_string(model_view_matrix) << "\n";
		//std::cout << "perspective matrix = " << glm::to_string(m_proj_matrix) << "\n";

		//Draw each mesh of the model.
		for (const auto& mesh : model_ptr->meshes())
		{
			m_ogl_invoker->invoke(glBindVertexArray, ARGS(mesh.VAO().value())); //TODO: Check how VAO is being dispersed to Mesh.
			//m_ogl_invoker->invoke(glBindBuffer, ARGS(GL_ARRAY_BUFFER, mesh.VBO().value()));
			//m_ogl_invoker->invoke(glVertexAttribPointer, ARGS(0, 3, GL_FLOAT, false, sizeof(rengage::model::Vertex), (GLvoid*)0));
			//m_ogl_invoker->invoke(glBindBuffer, ARGS(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO().value()));
			if (const auto& textures = mesh.Textures(); !textures.empty())
			{
				m_ogl_invoker->invoke(glActiveTexture, ARGS(GL_TEXTURE0));
				m_ogl_invoker->invoke(glBindTexture, ARGS(GL_TEXTURE_2D, mesh.Textures()[0]->handle()));
			}
			m_ogl_invoker->invoke(glDrawElements, ARGS(GL_TRIANGLES, mesh.indices().size(), GL_UNSIGNED_INT, nullptr));
			//m_ogl_invoker->invoke(glDrawArrays, ARGS(GL_TRIANGLES, 0, mesh.total_vertices()));
			m_ogl_invoker->invoke(glBindVertexArray, ARGS(0));
		}
		//m_ogl_invoker->invoke(glBindVertexArray, ARGS(0));
	}
}
