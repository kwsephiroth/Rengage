#pragma once
#include <GL/glew.h>
#include <string>

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
			//glDeleteShader(m_id);
		}

		//inline GLuint id() const { return m_id; }
		inline GLenum type() const { return m_type; }
		inline bool is_valid() const { return m_is_valid; }
		inline std::string source() const { return m_source; }
		inline std::string file_name() const { return m_file_name; }
		void delete_shader()
		{
			glDeleteShader(m_id);
			m_is_valid = false;
		}
		friend class ShaderFactory;
		friend class ShaderProgram;

	private:		
		Shader() = default;
		bool m_is_valid = false;
		GLuint m_id = 0;
		GLenum m_type = 0;
		std::string m_file_name;
		std::string m_source;
	};
}
