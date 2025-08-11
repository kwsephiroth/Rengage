#include "../../inc/rengage.lib/shader/shader_program.h"//TODO: Improve file include structure.

namespace rengage::shader
{

	ShaderProgram::ShaderProgram(std::shared_ptr<OGLInvoker> ogl_invoker, std::shared_ptr<ILogger> logger) :
		m_ogl_invoker(std::move(ogl_invoker)),
		m_logger(std::move(logger))
	{
		m_id = m_ogl_invoker->get_invoke(glCreateProgram);
	}

	ShaderProgram::~ShaderProgram()
	{
		std::cout << "~ShaderProgram() invoked!\n";
		//opengl_invoke(glDeleteProgram, ARGS(m_id));
	}

	std::unique_ptr<ShaderProgram> ShaderProgram::create_instance(
		const std::string& vertex_shader_path,
		const std::string& frag_shader_path,
		std::shared_ptr<OGLInvoker> ogl_invoker,
		std::shared_ptr<ILogger> logger)
	{
		rengage::shader::ShaderFactory shader_factory{ ogl_invoker, logger };//TODO: Inject dependencies into constructor.
		auto vertex_shader = shader_factory.load_shader_from_file(GL_VERTEX_SHADER, vertex_shader_path);
		auto frag_shader = shader_factory.load_shader_from_file(GL_FRAGMENT_SHADER, frag_shader_path);
		GLenum glError = glGetError();

		if (vertex_shader == nullptr || frag_shader == nullptr || !vertex_shader->is_valid() || !frag_shader->is_valid()) {
			LOG_ERROR(logger, "Failed to load shader(s). Check logs for error(s).");
			return nullptr;
		}

		std::unique_ptr<ShaderProgram> program(new ShaderProgram{ ogl_invoker, logger });
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
		m_ogl_invoker->invoke(glAttachShader, ARGS(m_id, shader_id));
	}

	bool ShaderProgram::link_program()
	{
		m_ogl_invoker->invoke(glLinkProgram, ARGS(m_id));

		//Log any linking errors.
		GLint success;
		const unsigned int MAX_LOG_SIZE = 512;
		GLchar info_log[MAX_LOG_SIZE];

		m_ogl_invoker->invoke(glGetProgramiv, ARGS(m_id, GL_LINK_STATUS, &success));

		if (success != GL_TRUE) {
			std::stringstream ss;
			m_ogl_invoker->invoke(glGetProgramInfoLog, ARGS(m_id, MAX_LOG_SIZE, nullptr, info_log));
			ss << "Failed to link shader program. Description below:\n";
			ss << info_log << "\n";
			LOG_ERROR(m_logger, ss.str());
			return false;
		}
		m_is_valid = true;
		return true;
	}

	void ShaderProgram::use()
	{
		m_ogl_invoker->invoke(glUseProgram, ARGS(m_id));
	}
}