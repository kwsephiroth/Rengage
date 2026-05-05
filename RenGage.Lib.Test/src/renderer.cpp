#include "../inc/renderer.h"
#include "../../RenGage.Lib/inc/rengage.lib/model/vertex.h"

namespace forest_escape {
	Renderer::Renderer(GLint program_id, GLint mv_index, GLint proj_index, float aspect_ratio) :
		m_program_id(program_id),
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
		
		static auto ogl_invoker = rengage::services::ServiceLocator::get_service<rengage::services::OGLInvoker>();
		
		auto model_matrix = glm::mat4(1.0f);
		auto use_texture_location = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "use_texture"));
		if (model_ptr->name() == "bat")
		{
			model_matrix = glm::translate(model_matrix, glm::vec3{ 5.0f, 3.0f, -2.0f });
			model_matrix *= glm::scale(model_matrix, glm::vec3{ 3.0f, 3.0f, 3.0f });	
			ogl_invoker->invoke(glUniform1i, ARGS(use_texture_location, 0));
		}

		auto model_view_matrix = m_camera->view_matrix() * model_matrix;
		//auto model_view_matrix =  m_camera->view_matrix() * model_ptr->model_matrix();
		
		ogl_invoker->invoke(glUniformMatrix4fv, ARGS(m_mv_index, 1, GL_FALSE, glm::value_ptr(model_view_matrix)));

		//Draw each mesh of the model.
		//ogl_invoker->invoke(glBindVertexArray, ARGS(model_ptr->VAO().value()));
		for (const auto& mesh : model_ptr->meshes())
		{
			ogl_invoker->invoke(glBindVertexArray, ARGS(mesh.VAO().value()));
			//if (const auto& textures = mesh.Textures(); !textures.empty())//TODO: Figure out why there can be more than one texture per mesh.
			//{
			//	//ogl_invoker->invoke(glActiveTexture, ARGS(GL_TEXTURE0));
			//	ogl_invoker->invoke(glBindTexture, ARGS(GL_TEXTURE_2D, mesh.Textures()[0]->handle()));
			//}
			//ogl_invoker->invoke(glBindBuffer, ARGS(GL_ARRAY_BUFFER, mesh.VBO().value()));
			//ogl_invoker->invoke(glEnableVertexAttribArray, ARGS(model_ptr->position_index().value()));
			//ogl_invoker->invoke(glVertexAttribPointer, ARGS(model_ptr->position_index().value(), 3, GL_FLOAT, false, sizeof(rengage::model::Vertex), (GLvoid*)0));
			//ogl_invoker->invoke(glBindBuffer, ARGS(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO().value()));
			//mesh.bind();
			apply_material(mesh); // TODO: This is temporary logic to apply material properties per mesh for now since we only have one material per mesh. Need to implement proper material system and shader uniform management later.
			ogl_invoker->invoke(glDrawElements, ARGS(GL_TRIANGLES, mesh.indices().size(), GL_UNSIGNED_INT, nullptr));
			ogl_invoker->invoke(glBindVertexArray, ARGS(0));
		}
		//ogl_invoker->invoke(glBindVertexArray, ARGS(0));

		//Reset model matrix. Temporary logic. TODO: remove later.
		model_view_matrix = m_camera->view_matrix() * glm::mat4{ 1.0f };
		ogl_invoker->invoke(glUniformMatrix4fv, ARGS(m_mv_index, 1, GL_FALSE, glm::value_ptr(model_view_matrix)));
		ogl_invoker->invoke(glUniform1i, ARGS(use_texture_location, 1));
	}

	void Renderer::apply_material(const rengage::model::Mesh& mesh)
	{
		if (mesh.materials().empty())
		{
			return;
		}

		auto material_ptr = mesh.materials()[0];
		float globalAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float ambientColor[4] = { material_ptr->GetAmbientColor().x, material_ptr->GetAmbientColor().y , material_ptr->GetAmbientColor().z , 1 };
		float diffuseColor[4] = { material_ptr->GetDiffuseColor().x, material_ptr->GetDiffuseColor().y , material_ptr->GetDiffuseColor().z , 1 };
		float specularColor[4] = { material_ptr->GetSpecularColor().x, material_ptr->GetSpecularColor().y , material_ptr->GetSpecularColor().z , 1 };
		float specularExponent = material_ptr->GetSpecularExponent();
		float* matAmb = ambientColor;
		float* matDif = diffuseColor;
		float* matSpe = specularColor;
		float matShi = specularExponent;

		GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, mambLoc, mdiffLoc, mspecLoc, mshiLoc;
		auto ogl_invoker = rengage::services::ServiceLocator::get_service<rengage::services::OGLInvoker>();
		// get the locations of the light and material fields in the shader
		globalAmbLoc = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "globalAmbient"));
		//ambLoc = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "light.ambient"));
		//diffLoc = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "light.diffuse"));
		//specLoc = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "light.specular"));
		//posLoc = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "light.position"));
		mambLoc = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "material.ambient"));
		mdiffLoc = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "material.diffuse"));
		mspecLoc = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "material.specular"));
		mshiLoc = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "material.shininess"));

		//  set the uniform light and material values in the shader
		ogl_invoker->invoke(glProgramUniform4fv, ARGS(m_program_id, globalAmbLoc, 1, globalAmbient));
		//glProgramUniform4fv(renderingProgram, ambLoc, 1, lightAmbient);
		//glProgramUniform4fv(renderingProgram, diffLoc, 1, lightDiffuse);
		//glProgramUniform4fv(renderingProgram, specLoc, 1, lightSpecular);
		//glProgramUniform3fv(renderingProgram, posLoc, 1, lightPos);
		ogl_invoker->invoke(glProgramUniform4fv, ARGS(m_program_id, mambLoc, 1, matAmb));
		ogl_invoker->invoke(glProgramUniform4fv, ARGS(m_program_id, mdiffLoc, 1, matDif));
		ogl_invoker->invoke(glProgramUniform4fv, ARGS(m_program_id, mspecLoc, 1, matSpe));
		ogl_invoker->invoke(glProgramUniform1f, ARGS(m_program_id, mshiLoc, matShi));

		auto default_color_location = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "default_color"));
		ogl_invoker->invoke(glUniform4f, ARGS(default_color_location, material_ptr->GetDiffuseColor().x, material_ptr->GetDiffuseColor().y, material_ptr->GetDiffuseColor().z, 1.0f));
	}
}
