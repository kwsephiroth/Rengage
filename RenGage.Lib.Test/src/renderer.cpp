#include "../inc/renderer.h"

namespace forest_escape {
	Renderer::Renderer()
	{
		init();
	}

	Renderer::~Renderer()
	{

	}

	bool Renderer::init()
	{
		if (!init_projection_matrix() &&
			!init_view_matrix())
		{
			return false;
		}
		return true;
	}

	bool Renderer::init_projection_matrix()
	{
		return true;
	}

	bool Renderer::init_view_matrix()
	{
		return true;
	}

	void Renderer::update_view_matrix(const glm::vec4& new_position)
	{
		
	}

	void Renderer::draw_frame()
	{

	}

	void Renderer::draw_model(const std::unique_ptr<rengage::model::Model>& model_ptr)
	{

	}
}
