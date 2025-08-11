#include "../inc/game_manager.h"

#define WINDOW_CALLBACK(function_name)\
	[](GLFWwindow* window, auto... args) {\
		auto pointer = static_cast<forest_escape::GameManager*>(glfwGetWindowUserPointer(window));\
		if(pointer) pointer->function_name(window, args...);\
	}

namespace forest_escape {

	GameManager::GameManager()
	{
		init();
	}

	GameManager::~GameManager()
	{
		//TODO: Cleanup OpenGL objects.
	}

	void GameManager::init()
	{
		m_logger = std::make_shared<rengage::logging::FileLogger>();

		if (auto p_logger = dynamic_cast<rengage::logging::FileLogger*>(m_logger.get()))
		{
			if (!p_logger->is_initialized())
			{
				rengage::logging::ConsoleLogger().log(rengage::logging::LogSeverity::ERROR, "Failed to instantiate logger.");
				return;
			}
		}
		else
		{
			rengage::logging::ConsoleLogger().log(rengage::logging::LogSeverity::ERROR, "Failed to instantiate logger.");
			return;
		}

		LOG_INFO(m_logger, "Initializing GameManager...");
		if (!init_window() ||
			!init_shader_program() ||
			!init_models())
		{
			LOG_ERROR(m_logger, "Failed to init GameManager. Check log for error(s).");
			exit(0);
		}

		m_program->use();//Installs the program object as part of the current rendering state.

		//TODO: Figure out constructor arguments for this class. Using default constructor for now.
		m_renderer = std::make_unique<Renderer>(
			m_ogl_invoker,
			m_ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "mv_matrix")),
			m_ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "proj_matrix")),
			m_window->aspect_ratio()
			);

		LOG_INFO(m_logger, "GameManager initialized!");
		m_initialized = true;
	}

	bool GameManager::init_window()
	{
		rengage::WindowAttributes window_attribs = { .name = "Forest Escape",
													.min_width = 1920,
													.min_height = 1080,
													.color = {0.0f, 0.0f, 0.0f, 1.0f},
													.swap_interval = 1 };//designated initializer since C++20

		m_window = std::make_unique<rengage::RenderingWindow>(m_ogl_invoker, m_logger, std::move(window_attribs));

		if (!m_window->initialized()) {
			LOG_ERROR(m_logger, "Rendering window was not properly initialized. Check logs for error(s).");
			return false;
		}

		auto glfw_ptr = m_window->glfw_window();
		glfwMakeContextCurrent(glfw_ptr);
		glfwSwapInterval(m_window->swap_interval());//Set vsync

		//Register GLFW window callback(s).
		glfwSetWindowUserPointer(glfw_ptr, this);//Enables GLFW to use our instance of RenderingWindow for callback invocation.
		glfwSetWindowSizeCallback(glfw_ptr, WINDOW_CALLBACK(on_window_resize));

		auto error_code = glewInit();//Glew must initialized in order to make OpenGL function calls.
		if (error_code != GLEW_OK) {
			LOG_ERROR(m_logger, "Failed to initialize GLEW with error code(" + std::to_string(error_code) + ").");
			return false;
		}

		LOG_INFO(m_logger, "OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)));
		return true;
	}

	bool GameManager::init_renderer()
	{
		return true;
	}

	bool GameManager::init_shader_program()
	{
		m_program = rengage::shader::ShaderProgram::create_instance("res/shaders/vertex_shader.glsl",
			"res/shaders/fragment_shader.glsl",
			m_ogl_invoker,
			m_logger);
		if (m_program == nullptr || !m_program->is_valid())
		{
			LOG_ERROR(m_logger, "Failed to create shader program. Check logs for error(s).");
			return false;
		}

		m_program_id = m_program->id();
		return true;
	}

	bool GameManager::init_models()
	{
		GLint position_index = m_ogl_invoker->get_invoke(glGetAttribLocation, ARGS(m_program->id(), "position"));
		GLint normal_index = m_ogl_invoker->get_invoke(glGetAttribLocation, ARGS(m_program->id(), "normal"));
		GLint tex_coord_index = m_ogl_invoker->get_invoke(glGetAttribLocation, ARGS(m_program->id(), "tex_coord"));

		unsigned int VAO = 0;
		rengage::model::ModelFactory model_factory{ m_ogl_invoker, m_logger };
		auto model = model_factory.load_model("res/models/pine_tree.obj",
			position_index,
			normal_index,
			tex_coord_index,
			VAO);

		if (!model)
		{
			return false;
		}

		m_models.emplace("pine_tree", std::move(model));
		//m_models.emplace("bat", std::move(model));

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
		if (m_game_loop_started || !m_initialized)
		{
			return;
		}

		m_game_loop_started = true;
		auto glfw_ptr = m_window->glfw_window();
		auto window_color = m_window->color();
		m_ogl_invoker->invoke(glEnable, ARGS(GL_DEPTH_TEST));
		m_ogl_invoker->invoke(glDepthFunc, ARGS(GL_LESS));

		while (!glfwWindowShouldClose(glfw_ptr))
		{
			m_ogl_invoker->invoke(glClearColor, ARGS(window_color.r, window_color.g, window_color.b, window_color.a));
			m_ogl_invoker->invoke(glClear, ARGS(GL_DEPTH_BUFFER_BIT));
			m_ogl_invoker->invoke(glClear, ARGS(GL_COLOR_BUFFER_BIT));
			draw_frame();
			glfwSwapBuffers(glfw_ptr);
			glfwPollEvents();
		}
		glfwTerminate();
	}

	void GameManager::draw_frame()
	{
		for (const auto& [model_name, model_ptr] : m_models)
		{
			//draw_model(model_ptr);
			m_renderer->draw_model(model_ptr);
		}
	}

	void GameManager::draw_model(const ModelPtr& model_ptr)
	{
		//opengl_invoke(glBindVertexArray, ARGS(model_ptr->VAO().value()));//Have to explicitly "get" optional value.
		//opengl_invoke(glDrawArrays, ARGS(GL_TRIANGLES, 0, model_ptr->total_vertices()));
		//std::cout << "Total vertices: " << model_ptr->total_vertices() << "\n";
	}

	void GameManager::on_window_resize(GLFWwindow* window, int width, int height)//TODO: Consider wrapping this in the Command design pattern.
	{
		LOG_INFO(m_logger, "on_window_resize invoked!");
		m_window->resize(width, height);
		//TODO: Refactor how projection matrix is updated.
		m_ogl_invoker->invoke(glViewport, ARGS(0, 0, width, height));
		m_renderer->set_aspect_ratio(m_window->aspect_ratio());
	}
}