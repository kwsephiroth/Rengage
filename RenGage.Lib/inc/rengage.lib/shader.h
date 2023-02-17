#pragma once
#include <GL/glew.h>
#include <string>

namespace rengage {
	class Shader
	{
	public:
		~Shader();
		inline GLuint id() const { return m_id; }
		inline GLuint type() const { return m_type; }
		inline bool is_valid() const { return m_is_valid; }
		friend class ShaderFactory;

	private:		
		Shader();
		bool m_is_valid = false;
		GLuint m_id;
		GLuint m_type;
		std::string m_file_name;
		std::string m_source;
	};
}
