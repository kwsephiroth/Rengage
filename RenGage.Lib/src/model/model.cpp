#include "../../inc/rengage.lib/model/model.h"

namespace rengage::model {

	void Model::setup_VAO()
	{
		////Initialize to dummy values. Will be overwritten with valid ids.
		m_vao = 0;

		std::cout << "old m_vao = " << m_vao.value() << "\n";
		glGenVertexArrays(1, &m_vao.value());
		std::cout << "new m_vao = " << m_vao.value() << "\n";
	}
}