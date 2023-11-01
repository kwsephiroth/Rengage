#pragma once
#include <GL/glew.h>
#include <vector>
#include "mesh.h"

namespace rengage::model {
	class Model
	{
	private:
		Model() = default;//TODO: Create public constructor that takes model dependencies as parameters.
		std::vector<Mesh> m_meshes;
		unsigned int m_num_meshes;
		bool m_initialized = false;

		//VAO should be generated ONLY after the model is successfully initialized.
		std::optional<unsigned int> m_VAO = std::nullopt;//vertex attribute object(VAO) id
		VertexAttributeIndex m_position_index;
		VertexAttributeIndex m_normal_index;
		VertexAttributeIndex m_tex_coord_index;

		void setup_VAO(const unsigned int VAO, const VertexAttributeIndex position_index, const VertexAttributeIndex normal_index, const VertexAttributeIndex tex_coord_index);
		void register_VBOs(const VertexAttributeIndex position_index, const VertexAttributeIndex normal_index, const VertexAttributeIndex tex_coord_index);
	public:
		~Model() = default;
		friend class ModelFactory;
		std::optional<unsigned int> VAO() { return m_VAO; }
	};
};
