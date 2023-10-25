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
		std::optional<unsigned int> m_vao = std::nullopt;//vertex attribute object(VAO) id

		void setup_VAO();
	public:
		~Model() = default;
		friend class ModelFactory;
		std::optional<unsigned int> VAO() { return m_vao; }
	};
};
