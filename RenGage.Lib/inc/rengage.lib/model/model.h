#pragma once
#include <vector>
#include "mesh.h"

namespace rengage::model {
	class Model
	{
	private:
		Model() = default;
		std::vector<Mesh> m_meshes;
		unsigned int m_num_meshes;

	public:
		~Model() = default;
		friend class ModelFactory;
	};
};