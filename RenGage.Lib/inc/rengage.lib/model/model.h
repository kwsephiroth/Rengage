#pragma once
#include <vector>
#include "mesh.h"

namespace rengage::model {
	class Model
	{
	private:
		std::vector<Mesh> m_meshes;

	public:
		Model() = default;
		~Model() = default;
	};
};
