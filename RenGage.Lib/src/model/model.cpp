#include "../../inc/rengage.lib/model/model.h"

namespace rengage::model {

	void Model::setup_VAO(unsigned int VAO, const VertexAttributeIndex position_index, const VertexAttributeIndex normal_index, const VertexAttributeIndex tex_coord_index)
	{
		//Copy ids
		m_VAO = VAO;
		m_position_index = position_index;
		m_normal_index = normal_index;
		m_tex_coord_index = tex_coord_index;

		glBindVertexArray(m_VAO.value());
		register_VBOs(position_index, normal_index, tex_coord_index);//Associate all VBOs with currently bound VAO
	}

	void Model::register_VBOs(const VertexAttributeIndex position_index, const VertexAttributeIndex normal_index, const VertexAttributeIndex tex_coord_index)
	{
		for (auto& mesh : m_meshes)
		{
			mesh.register_VBO(position_index, normal_index, tex_coord_index);
		}
	}
}