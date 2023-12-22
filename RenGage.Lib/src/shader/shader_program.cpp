#include "../../inc/rengage.lib/shader/shader_program.h"//TODO: Improve file include structure.

namespace rengage::shader
{
	std::unique_ptr<ShaderProgram> ShaderProgram::create_instance(const std::string& vertex_shader_path,
																  const std::string& frag_shader_path)
	{
		auto vertex_shader = rengage::shader::ShaderFactory::load_shader_from_file(GL_VERTEX_SHADER, vertex_shader_path);
		auto frag_shader = rengage::shader::ShaderFactory::load_shader_from_file(GL_FRAGMENT_SHADER, frag_shader_path);

		if (vertex_shader == nullptr || frag_shader == nullptr || !vertex_shader->is_valid() || !frag_shader->is_valid()) {
			LOG_ERROR("Failed to load shader(s). Check logs for error(s).");
			return nullptr;
		}

		ShaderProgram program;
		program.attach_shader(vertex_shader->id());
		program.attach_shader(frag_shader->id());
		if (!program.link_program())
		{
			return nullptr;
		}
		return nullptr;
	}

	void ShaderProgram::attach_shader(GLuint shader_id)
	{
		glAttachShader(m_id, shader_id);//TODO: Call with logging GLCall function.
	}

	bool ShaderProgram::link_program()
	{
		glLinkProgram(m_id);
		
		//Log any linking errors.
		GLint success;
		const unsigned int MAX_LOG_SIZE = 512;
		GLchar info_log[MAX_LOG_SIZE];

		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			std::stringstream ss;

			glGetProgramInfoLog(m_id, MAX_LOG_SIZE, NULL, info_log);

			ss << "Failed to link shader program. Description below:\n";
			ss << info_log << "\n";
			LOG_ERROR(ss.str())
			return false;
		}
		return true;
	}

	void ShaderProgram::use()
	{

	}
}