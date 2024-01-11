#include "../../inc/rengage.lib/model/model.h"

namespace rengage::model {

	void Model::setup_VAO(GLuint VAO, const GLint position_index, const GLint normal_index, const GLint tex_coord_index)
	{
		//Copy ids
		m_VAO = VAO;
		m_position_index = position_index;
		m_normal_index = normal_index;
		m_tex_coord_index = tex_coord_index;

		opengl_invoke(glBindVertexArray, ARGS(m_VAO.value()));
		register_VBOs(position_index, normal_index, tex_coord_index);//Associate all VBOs with currently bound VAO
	}

	void Model::register_VBOs(const GLint position_index, const GLint normal_index, const GLint tex_coord_index)
	{
		for (auto& mesh : m_meshes)
		{
			mesh.register_VBO(position_index, normal_index, tex_coord_index);
		}
	}
}