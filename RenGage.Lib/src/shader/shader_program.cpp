#include "../../inc/rengage.lib/shader/shader_program.h"//TODO: Improve file include structure.

namespace rengage::shader
{

	ShaderProgram::ShaderProgram()
	{
		m_id = opengl_get_invoke(glCreateProgram);
		//std::cout << "m_id = " << m_id << "\n";
	}

	ShaderProgram::~ShaderProgram()
	{
		std::cout << "~ShaderProgram() invoked!\n";
		//opengl_invoke(glDeleteProgram, ARGS(m_id));
	}

	std::unique_ptr<ShaderProgram> ShaderProgram::create_instance(const std::string& vertex_shader_path,
																  const std::string& frag_shader_path)
	{
		auto vertex_shader = rengage::shader::ShaderFactory::load_shader_from_file(GL_VERTEX_SHADER, vertex_shader_path);
		auto frag_shader = rengage::shader::ShaderFactory::load_shader_from_file(GL_FRAGMENT_SHADER, frag_shader_path);
		GLenum glError = glGetError();

		if (vertex_shader == nullptr || frag_shader == nullptr || !vertex_shader->is_valid() || !frag_shader->is_valid()) {
			LOG_ERROR("Failed to load shader(s). Check logs for error(s).");
			return nullptr;
		}

		std::unique_ptr<ShaderProgram> program(new ShaderProgram);
		//ShaderProgram* program = new ShaderProgram;//Create shader program object.
		program->attach_shader(vertex_shader->m_id);
		program->attach_shader(frag_shader->m_id);
		if (!program->link_program())
		{
			return nullptr;
		}
		//TODO: Figure out when and where to delete shaders.
		//glDeleteShader(vertex_shader->m_id);
		//glDeleteShader(frag_shader->m_id);
		return program;
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

		if (success != GL_TRUE) {
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
		glUseProgram(m_id);
	}
}