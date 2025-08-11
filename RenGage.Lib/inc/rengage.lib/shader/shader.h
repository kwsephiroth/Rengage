#pragma once
#include <GL/glew.h>
#include <string>
#include "../tools/ogl_invoker.h"

namespace rengage::shader
{
	struct ShaderFileInfo
	{
		GLenum type;
		std::string file_name;
	};

	class Shader
	{
	public:
		~Shader()
		{
			//TODO: Figure out when and where to delete the shader.
			//glDeleteShader(m_id);
		}

		//inline GLuint id() const { return m_id; }
		inline GLenum type() const { return m_type; }
		inline bool is_valid() const { return m_is_valid; }
		inline std::string source() const { return m_source; }
		inline std::string file_name() const { return m_file_name; }
		void delete_shader()
		{
			m_ogl_invoker->invoke(glDeleteShader, ARGS(m_id));
			m_is_valid = false;
		}
		friend class ShaderFactory;
		friend class ShaderProgram;

	private:
		Shader(std::shared_ptr<OGLInvoker> oglInvoker) : m_ogl_invoker(std::move(oglInvoker)) {}

		std::shared_ptr<OGLInvoker> m_ogl_invoker;
		bool m_is_valid = false;
		GLuint m_id = 0;
		GLenum m_type = 0;
		std::string m_file_name;
		std::string m_source;
	};
}
