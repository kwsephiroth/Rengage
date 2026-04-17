#pragma once
#include <GL/glew.h>
#include <memory>
#include "shader.h"
#include "shader_factory.h"

namespace rengage::shader
{
	class ShaderProgram
	{
	public:
		~ShaderProgram();
		static std::unique_ptr<ShaderProgram> create_instance(
			const std::string& vertex_shader_path,
			const std::string& frag_shader_path);

		void attach_shader(GLuint shader_id);
		void use();
		inline GLuint id() const { return m_id; }
		inline bool is_valid() const { return m_is_valid; }

	private:
		ShaderProgram();
		bool link_program();

		GLuint m_id;
		bool m_is_valid = false;
		std::shared_ptr<services::logging::ILogger> m_logger;
	};
}

