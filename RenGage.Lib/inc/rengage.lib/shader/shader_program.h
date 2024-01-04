#pragma once
#include <GL/glew.h>
#include <memory>
#include "../logging/logger_macros.h"
#include "shader.h"
#include "shader_factory.h"

namespace rengage::shader
{
	class ShaderProgram
	{
	public:
		~ShaderProgram() { std::cout << "~ShaderProgram() invoked!\n"; glDeleteProgram(m_id); }
		static std::unique_ptr<ShaderProgram> create_instance(const std::string& vertex_shader_path,
															  const std::string& frag_shader_path);

		void attach_shader(GLuint shader_id);
		void use();
		inline GLuint id() const { return m_id; }

	private:
		ShaderProgram()
		{
			m_id = glCreateProgram();
		}
		bool link_program();

		GLuint m_id;
	};
}

