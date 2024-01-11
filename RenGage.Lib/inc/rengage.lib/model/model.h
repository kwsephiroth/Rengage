#pragma once
#include <GL/glew.h>
#include <vector>
#include "mesh.h"
#include "../tools/opengl_invoke.h"

namespace rengage::model {
	class Model
	{
	private:
		Model() = default;//TODO: Create public constructor that takes model dependencies as parameters.
		std::vector<Mesh> m_meshes;
		unsigned int m_num_meshes;
		bool m_initialized = false;

		//VAO should be generated ONLY after the model is successfully initialized.
		std::optional<GLuint> m_VAO = std::nullopt;//vertex attribute object(VAO) id
		std::optional<GLint> m_position_index = std::nullopt;
		std::optional<GLint> m_normal_index = std::nullopt;
		std::optional<GLint> m_tex_coord_index = std::nullopt;

		void setup_VAO(const GLuint VAO, const GLint position_index, const GLint normal_index, const GLint tex_coord_index);
		void register_VBOs(const GLint position_index, const GLint normal_index, const GLint tex_coord_index);
	public:
		~Model() = default;
		friend class ModelFactory;
		std::optional<GLuint> VAO() { return m_VAO; }
	};
};
