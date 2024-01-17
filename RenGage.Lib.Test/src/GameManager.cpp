#include "../inc/GameManager.h"

namespace forest_escape {
	
	GameManager::GameManager()
	{
		init();
	}

	GameManager::~GameManager()
	{

	}

	void GameManager::init()
	{
		LOG_INFO("Initializing GameManager...")
		if (!init_window() ||
			!init_shader_program() ||
			!init_models())
		{
			LOG_ERROR("Failed to init GameManager. Check log for error(s).")
			exit(0);
		}

		//Fetch and store uniform indices once.
		//opengl_invoke(glUseProgram, ARGS(m_program_id));
		m_mv_index = opengl_get_invoke(glGetUniformLocation, ARGS(m_program_id, "mv_matrix"));
		m_proj_index = opengl_get_invoke(glGetUniformLocation, ARGS(m_program_id, "proj_matrix"));
		std::cout << "mv_matrix_index = " << m_mv_index << "\nproj_matrix_index = " << m_proj_index << "\n";

		LOG_INFO("GameManager initialized!")
	}

	bool GameManager::init_window()
	{
		rengage::WindowAttributes window_attribs = {.name = "Forest Escape", 
													.min_width = 1920, 
													.min_height = 1080, 
													.color = {0.0f, 0.0f, 1.0f, 1.0f},
													.swap_interval = 1 };//designated initializer since C++20

		m_window = std::make_unique<rengage::RenderingWindow>(std::move(window_attribs));

		if (!m_window->initialized()) {
			LOG_ERROR("Rendering window was not properly initialized. Check logs for error(s).")
				return false;
		}

		auto window_ptr = m_window->get();
		glfwMakeContextCurrent(window_ptr);
		glfwSwapInterval(m_window->swap_interval());//Set vsync

		auto error_code = glewInit();//Glew must initialized in order to make OpenGL function calls.
		if (error_code != GLEW_OK) {
			LOG_ERROR("Failed to initialize GLEW with error code(" + std::to_string(error_code) + ").");
			return false;
		}
		LOG_INFO("OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)));
		return true;
	}

	bool GameManager::init_shader_program()
	{
		m_program = rengage::shader::ShaderProgram::create_instance("res/shaders/vertex_shader.glsl",
																		   "res/shaders/fragment_shader.glsl");
		if (m_program == nullptr || !m_program->is_valid())
		{
			LOG_ERROR("Failed to create shader program. Check logs for error(s).");
			return false;
		}

		m_program_id = m_program->id();

		return true;
	}

	bool GameManager::init_models()
	{
		GLint position_index = opengl_get_invoke(glGetAttribLocation, ARGS(m_program->id(), "position"));
		GLint normal_index = opengl_get_invoke(glGetAttribLocation, ARGS(m_program->id(), "normal"));
		GLint tex_coord_index = opengl_get_invoke(glGetAttribLocation, ARGS(m_program->id(), "tex_coord"));

		unsigned int VAO = 0;
		opengl_invoke(glGenVertexArrays, ARGS(1, &VAO));

		auto model = rengage::model::ModelFactory::load_model(  "res/models/pine_tree.obj",
																position_index,
																normal_index,
																tex_coord_index,
																VAO);
		if (!model)
		{
			return false;
		}

		m_models.emplace("pine_tree", std::move(model));

		return true;
	}

	bool GameManager::program_is_valid()
	{
		return (m_program != nullptr && m_program->is_valid());
	}

	bool GameManager::init_uniform_indices()
	{
		return true;
	}

	void GameManager::start_game_loop()
	{
		auto window_ptr = m_window->get();
		auto window_color = m_window->color();

		while (!glfwWindowShouldClose(window_ptr))
		{
			opengl_invoke(glClear, ARGS(GL_DEPTH_BUFFER_BIT));
			opengl_invoke(glClearColor, ARGS(window_color.r, window_color.g, window_color.b, window_color.a));
			opengl_invoke(glClear, ARGS(GL_COLOR_BUFFER_BIT));
			draw_frame();
			glfwSwapBuffers(window_ptr);
			glfwPollEvents();
		}
		glfwTerminate();
	}

	void GameManager::draw_frame()
	{
		for (const auto& [model_name, model_ptr] : m_models)
		{
			draw_model(model_ptr);
		}
	}

	void GameManager::draw_model(const std::unique_ptr<rengage::model::Model>& model_ptr)
	{
		//opengl_invoke(glBindVertexArray, ARGS(model_ptr->VAO()));
		//opengl_invoke(glDrawArrays, ARGS(GL_TRIANGLES, 0 < number of vertices > ));
	}
}