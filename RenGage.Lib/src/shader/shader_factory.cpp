#include "../../inc/rengage.lib/shader/shader_factory.h"//TODO: Improve file include structure.

namespace rengage::shader
{
	std::unique_ptr<Shader> ShaderFactory::load_shader_from_file(const GLenum type, const std::string& filename)
	{
		std::ifstream input_file;
		std::unique_ptr<Shader> shader_ptr = nullptr;

		input_file.open(filename);
		if (!input_file.good()) {
			LOG_ERROR(m_logger, "Error opening file named '" + std::string{ filename } + "'. Please check file or filename.");
			return shader_ptr;
		}

		std::string source;
		std::string line;

		while (!input_file.eof()) {
			getline(input_file, line);
			source.append(line + "\n");
		}
		input_file.close();

		auto shader_id = m_ogl_invoker->get_invoke(glCreateShader, ARGS(type));
		auto shader_source_ptr = source.c_str();
		auto success = compile_shader_source(shader_id, shader_source_ptr, filename);

		if (success == GL_TRUE) {
			shader_ptr = std::unique_ptr<Shader>(new Shader(m_ogl_invoker));
			shader_ptr->m_id = shader_id;
			shader_ptr->m_is_valid = true;
			shader_ptr->m_source = std::move(source);
			shader_ptr->m_type = type;
			shader_ptr->m_file_name = filename;
		}

		return shader_ptr;
	}

	std::unique_ptr<Shader> ShaderFactory::load_shader_from_source(const GLenum type, const std::string& source)
	{
		std::unique_ptr<Shader> shader_ptr = nullptr;
		GLenum shader_id = m_ogl_invoker->get_invoke(glCreateShader, ARGS(type));
		auto success = compile_shader_source(shader_id, source);

		if (success == GL_TRUE) {
			shader_ptr = std::unique_ptr<Shader>(new Shader(m_ogl_invoker));//Can't use make_unique here due to private constructor.
			shader_ptr->m_id = shader_id;
			shader_ptr->m_is_valid = true;
			shader_ptr->m_source = source;
			shader_ptr->m_type = type;
		}

		return shader_ptr;
	}

	GLint ShaderFactory::compile_shader_source(const GLuint shader_id, const std::string& source, const std::string& filename)
	{
		const GLchar* source_cstr = source.c_str();
		m_ogl_invoker->invoke(glShaderSource, ARGS(shader_id, 1, &source_cstr, nullptr));
		m_ogl_invoker->invoke(glCompileShader, ARGS(shader_id));
		GLint success;
		m_ogl_invoker->invoke(glGetShaderiv, ARGS(shader_id, GL_COMPILE_STATUS, &success));

		if (success != GL_TRUE) {
			GLsizei actual_log_length = 0;
			const unsigned int MAX_LOG_LENGTH = 1024;
			GLchar info_log[MAX_LOG_LENGTH];

			m_ogl_invoker->invoke(glGetShaderInfoLog, ARGS(shader_id, MAX_LOG_LENGTH, &actual_log_length, info_log));

			std::stringstream ss;
			ss << "\nSHADER COMPILATION FAILURE: \n";
			if (!filename.empty()) {
				ss << "Filename: '" << filename << "'\n";
			}
			else {
				ss << "Source:\n\"" << source << "\"\n";
			}
			ss << "Log: " << info_log << "\n";
			LOG_ERROR(m_logger, ss.str());
		}

		return success;
	}
}