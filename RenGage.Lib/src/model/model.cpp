#include "../../inc/rengage.lib/model/model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace rengage::model {

	void Model::setup_VAO(GLuint VAO, const GLint position_index, const GLint normal_index, const GLint tex_coord_index)
	{
		//Copy ids
		m_vao = VAO;
		m_position_index = position_index;
		m_normal_index = normal_index;
		m_tex_coord_index = tex_coord_index;

		//m_model_matrix = glm::mat4(1.0f);//Initialize to identity matrix.
		m_model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, -25.0f)); // This will be the last transformation applied to the model matrix.
		glm::vec3 euler_angles(glm::radians(10.0f), 0.0f, 0.0f);
		m_model_matrix *= glm::toMat4(glm::quat(euler_angles));
		register_VBOs(position_index, normal_index, tex_coord_index);//Associate all VBOs with currently bound VAO
		m_initialized = true;
	}
	
	void Model::register_VBOs(const GLint position_index, const GLint normal_index, const GLint tex_coord_index)
	{
		for (auto& mesh : m_meshes)
		{
			mesh.register_VBO(position_index, normal_index, tex_coord_index);
		}
	}
}