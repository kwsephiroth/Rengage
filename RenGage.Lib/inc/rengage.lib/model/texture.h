#pragma once
#include <GL/glew.h>
#include <SOIL2/SOIL2.h>
#include <string>
#include "../services/logging/logger_macros.h"
#include "../services/service_locator.h"

namespace rengage::model {
	class Texture
	{
	public:
		Texture(const std::filesystem::path& filename);
		const std::string filename() const { return m_filepath.string(); } //TODO: Update this to return a reference rather than a copy.
		const GLuint handle() const { return m_handle; }
		const bool valid() const { return m_valid; }

	private:
		bool load();
		std::filesystem::path m_filepath;
		std::shared_ptr<services::logging::ILogger> m_logger;
		GLuint m_handle;// The Opengl texture handle
		bool m_valid;
	};
}

