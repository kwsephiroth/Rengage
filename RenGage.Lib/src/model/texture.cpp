#include "../../inc/rengage.lib/model/texture.h"

namespace rengage::model {
	Texture::Texture(const std::filesystem::path& filename, std::shared_ptr<OGLInvoker> ogl_invoker) :
		m_filepath(filename),
		m_ogl_invoker(ogl_invoker),
		m_handle(0),
		m_valid(false)
	{
		if (load())
		{
			m_valid = true;
		}
	}

	bool Texture::load()
	{
		m_handle = SOIL_load_OGL_texture(m_filepath.string().c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);//TODO: figure out why this flag inverts the branch texture.
		if (m_handle == 0)
		{
			LOG_ERROR("Failed to load texture path '" + m_filepath.string() + "'.");
			return false;
		}

		// TODO: Make the following section configuration by the client.
		// ----- mipmap/anisotropic section
		m_ogl_invoker->invoke(glBindTexture, ARGS(GL_TEXTURE_2D, m_handle));
		m_ogl_invoker->invoke(glTexParameteri, ARGS(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		m_ogl_invoker->invoke(glGenerateMipmap, ARGS(GL_TEXTURE_2D));
		if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
			GLfloat anisoset = 0.0f;
			m_ogl_invoker->invoke(glGetFloatv, ARGS(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoset));
			m_ogl_invoker->invoke(glTexParameterf, ARGS(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoset));
		}
		// ----- end of mipmap/anisotropic section

		return true;
	}
}