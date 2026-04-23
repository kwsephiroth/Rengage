#include "../../inc/rengage.lib/model/model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace rengage::model {

	void Model::setup_VAO(GLuint vao, const GLint position_index, const GLint normal_index, const GLint tex_coord_index)
	{
		//Copy ids
		m_vao = vao;
		m_position_index = position_index;
		m_normal_index = normal_index;
		m_tex_coord_index = tex_coord_index;

		m_model_matrix = glm::mat4(1.0f);//Initialize to identity matrix.
		//m_model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, -25.0f)); // This will be the last transformation applied to the model matrix.
		//glm::vec3 euler_angles(glm::radians(10.0f), 0.0f, 0.0f);
		//m_model_matrix *= glm::toMat4(glm::quat(euler_angles));
		register_VBOs(vao, position_index, normal_index, tex_coord_index);//Associate all VBOs with currently bound VAO
		m_initialized = true;
	}
	
	void Model::register_VBOs(const GLuint vao, const GLint position_index, const GLint normal_index, const GLint tex_coord_index)
	{
		auto ogl_invoker = services::ServiceLocator::get_service<services::OGLInvoker>();
		ogl_invoker->invoke(glBindVertexArray, ARGS(vao));//Bind VAO - associates following buffers/atrrib pointers with this vao's state.
		for (auto& mesh : m_meshes)
		{
			mesh.register_VBO(vao, position_index, normal_index, tex_coord_index);
		}
		ogl_invoker->invoke(glBindVertexArray, ARGS(0));//Unbind VAO
	}
}