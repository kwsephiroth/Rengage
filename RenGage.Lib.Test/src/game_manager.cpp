#include "../inc/game_manager.h"

namespace forest_escape {

	namespace
	{
		GLuint planeVAO;
		GLuint planeVBO;
		void setup_plane_vbo(const GLint position_index)
		{
			float planeVertices[18] =
			{
				//Triangle #1
				//x, y, z				   `	 //r, g, b, a
				  100.0f, -0.02f,  100.0f,       //0.0f, 1.0f, 0.0f, 1.0f,
				 -100.0f, -0.02f,  100.0f,       //0.0f, 1.0f, 0.0f, 1.0f,
				 -100.0f, -0.02f, -100.0f,       //0.0f, 1.0f, 0.0f, 1.0f,

				 //Triangle #2
				  100.0f, -0.02f,  100.0f,      // 0.0f, 1.0f, 0.0f, 1.0f,
				 -100.0f, -0.02f, -100.0f,      // 0.0f, 1.0f, 0.0f, 1.0f,
				  100.0f, -0.02f, -100.0f,      // 0.0f, 1.0f, 0.0f, 1.0f,
			};
			glGenVertexArrays(1, &planeVAO);
			glBindVertexArray(planeVAO);
			glGenBuffers(1, &planeVBO);
			glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(position_index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
			glEnableVertexAttribArray(position_index);
			glBindVertexArray(0);
		}

		void draw_plane()
		{
			glBindVertexArray(planeVAO);
			glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}

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
		LOG_INFO("Initializing GameManager...");
		if (!init_window() ||
			!init_shader_program() ||
			!init_models())
		{
			LOG_ERROR("Failed to init GameManager. Check log for error(s).");
			exit(0);
		}

		m_program->use();//Installs the program object as part of the current rendering state.
		auto ogl_invoker = rengage::services::ServiceLocator::get_service<rengage::services::OGLInvoker>();
		m_renderer = std::make_unique<Renderer>(
			ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "mv_matrix")),
			ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "proj_matrix")),
			m_window->aspect_ratio()
		);

		// Setup camera controller as observer to input handlers.
		m_camera_controller = std::make_unique < rengage::camera::CameraController >(m_renderer->m_camera.get());
		m_keyboard_input_handler->add_observer(m_camera_controller.get());
		//TODO: Consider using Command pattern instead of Observer since we don't want different entities handling the same key press in different ways.
		m_keyboard_input_handler->add_observer(this);// To observe escape key for closing the main window.
		m_mouse_input_handler->add_observer(m_camera_controller.get());

		// Set initial cursor position to middle of screen.
		glfwSetInputMode(m_window->glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);// Confine cursor to window and hide it.
		glfwSetCursorPos(m_window->glfw_window(), m_window->width() / 2, m_window->height() / 2);
		//		double cursor_x, cursor_y;
		//		glfwGetCursorPos(m_window->glfw_window(), &cursor_x, &cursor_y);
		//		m_camera_controller->on_notify(rengage::EventType::MouseMoved, glm::vec2{ cursor_x, cursor_y });

		LOG_INFO("GameManager initialized!");
		m_initialized = true;
	}

	bool GameManager::init_window()
	{
		rengage::WindowAttributes window_attribs = { .name = "Forest Escape",
													.min_width = rengage::RES_1440P.horizontal,
													.min_height = rengage::RES_1440P.vertical,
													.color = {135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 244.0f, 1.0f}, //TODO: Add color helper function somewhere.
													.swap_interval = 1 };//designated initializer since C++20

		m_window = std::make_unique<rengage::RenderingWindow>(std::move(window_attribs), false);

		if (!m_window->initialized()) {
			LOG_ERROR("Rendering window was not properly initialized. Check logs for error(s).");
			return false;
		}

		auto glfw_ptr = m_window->glfw_window();
		glfwMakeContextCurrent(glfw_ptr);
		glfwSwapInterval(m_window->swap_interval());//Set vsync

		// Initialize input handlers.
		m_keyboard_input_handler = std::make_unique<input::KeyboardInputHandler>();
		m_mouse_input_handler = std::make_unique<input::MouseInputHandler>();

		// Register handlers for window events.

		// TODO: Create macro for binding member functions as event handlers to reduce boilerplate code and improve readability.
		using namespace std::placeholders;
		m_window->register_resize_handler(std::bind(&GameManager::on_window_resize, this, _1, _2, _3));
		m_window->register_key_event_handler(std::bind(&input::KeyboardInputHandler::handle_key_event,
			m_keyboard_input_handler.get(),
			_1, _2, _3, _4, _5));
		m_window->register_char_event_handler(std::bind(&input::KeyboardInputHandler::handle_char_event,
			m_keyboard_input_handler.get(),
			_1, _2));
		m_window->register_mouse_movement_handler(std::bind(&input::MouseInputHandler::handle_mouse_movement,
			m_mouse_input_handler.get(),
			_1, _2, _3));
		m_window->register_mouse_button_handler(std::bind(&input::MouseInputHandler::handle_mouse_button,
			m_mouse_input_handler.get(),
			_1, _2, _3, _4));
		m_window->register_mouse_scroll_handler(std::bind(&input::MouseInputHandler::handle_mouse_scroll,
			m_mouse_input_handler.get(),
			_1, _2, _3));

		auto error_code = glewInit();//Glew must initialized in order to make OpenGL function calls.
		if (error_code != GLEW_OK) {
			LOG_ERROR("Failed to initialize GLEW with error code(" + std::to_string(error_code) + ").");
			return false;
		}

		LOG_INFO("OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)));
		return true;
	}

	bool GameManager::init_renderer()
	{
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
		auto ogl_invoker = rengage::services::ServiceLocator::get_service<rengage::services::OGLInvoker>();
		GLint position_index = ogl_invoker->get_invoke(glGetAttribLocation, ARGS(m_program->id(), "position"));
		GLint normal_index = ogl_invoker->get_invoke(glGetAttribLocation, ARGS(m_program->id(), "normal"));
		GLint tex_coord_index = ogl_invoker->get_invoke(glGetAttribLocation, ARGS(m_program->id(), "tex_coord"));

		//m_vao = 0;
		//ogl_invoker->invoke(glGenVertexArrays, ARGS(1, &m_vao));
		//planeVAO = m_vao;//TODO: Remove this later when plane is properly implemented as a model and not just hardcoded vertices in the GameManager.

		rengage::model::ModelFactory model_factory{};
		auto model = model_factory.load_model({
			.file_path = "res/models/pine_tree.obj",
			.position_index = position_index,
			.normal_index = normal_index,
			.tex_coord_index = tex_coord_index,
			.textures_dir = "res/textures"
			});

		if (!model || !model->initialized())
		{
			return false;
		}

		m_models.emplace("pine_tree", std::move(model));

		//model = model_factory.load_model({
		//	.file_path = "res/models/bat.obj",
		//	.position_index = position_index,
		//	.normal_index = normal_index,
		//	.tex_coord_index = tex_coord_index,
		//	.vao = VAO,
		//	.textures_dir = "res/textures"
		//	});

		//if (!model || !model->initialized())
		//	return false;

		//m_models.emplace("bat", std::move(model));

		//TEST CODE ONLY // TODO: Remove later
		setup_plane_vbo(position_index);

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
		auto ogl_invoker = rengage::services::ServiceLocator::get_service<rengage::services::OGLInvoker>();
		ogl_invoker->invoke(glEnable, ARGS(GL_DEPTH_TEST));
		ogl_invoker->invoke(glDepthFunc, ARGS(GL_LESS));
		ogl_invoker->invoke(glEnable, ARGS(GL_BLEND));
		ogl_invoker->invoke(glBlendFunc, ARGS(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		//ogl_invoker->invoke(glEnable, ARGS(GL_ALPHA_TEST));
		//ogl_invoker->invoke(glAlphaFunc, ARGS(GL_GREATER, 0.1f));
		//ogl_invoker->invoke(glEnable, ARGS(GL_CULL_FACE));
		//ogl_invoker->invoke(glCullFace, ARGS(GL_FRONT));

		while (!glfwWindowShouldClose(glfw_ptr))
		{
			ogl_invoker->invoke(glClearColor, ARGS(window_color.r, window_color.g, window_color.b, window_color.a));
			ogl_invoker->invoke(glClear, ARGS(GL_DEPTH_BUFFER_BIT));
			ogl_invoker->invoke(glClear, ARGS(GL_COLOR_BUFFER_BIT));
			m_camera_controller->process_key_input();

			// Draw plane first since it should be behind all other objects in the scene. This is a temporary solution until a more robust rendering system with proper depth sorting is implemented.
			// Think "Painter's Algorithm" for now. We can implement a more robust solution later that utilizes a depth buffer and proper sorting of transparent objects.
			auto use_texture_location = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "use_texture"));
			auto default_color_location = ogl_invoker->get_invoke(glGetUniformLocation, ARGS(m_program_id, "default_color"));
			ogl_invoker->invoke(glUniform1i, ARGS(use_texture_location, 0));
			ogl_invoker->invoke(glUniform4f, ARGS(default_color_location, 46.0f / 255.0f, 111.0f / 255.0f, 64.0f / 255.0f, 1.0f));
			draw_plane();
			ogl_invoker->invoke(glUniform1i, ARGS(use_texture_location, 1));

			draw_frame();
			glfwSwapBuffers(glfw_ptr);
			glfwPollEvents();
		}
		glfwTerminate();
	}

	void GameManager::draw_frame()
	{
		for (const auto& [_, model_ptr] : m_models)
		{
			m_renderer->draw_model(model_ptr);
		}
	}

	void GameManager::on_window_resize(GLFWwindow* window, int width, int height)//TODO: Consider wrapping this in the Command design pattern.
	{
		//LOG_INFO("on_window_resize invoked!");
		std::cout << "on_window_resize invoked!\n";
		m_window->resize(width, height);
		//TODO: Refactor how projection matrix is updated.
		auto ogl_invoker = rengage::services::ServiceLocator::get_service<rengage::services::OGLInvoker>();
		ogl_invoker->invoke(glViewport, ARGS(0, 0, width, height));
		m_renderer->set_aspect_ratio(m_window->aspect_ratio());
	}

	void GameManager::on_notify(rengage::EventType event_type, rengage::EventArgs event_args)
	{
		switch (event_type)
		{
		case rengage::EventType::KeyPressed:
		{
			try
			{
				auto key = std::any_cast<rengage::Key>(event_args);

				switch (key)
				{
				case GLFW_KEY_ESCAPE:
				{
					glfwSetWindowShouldClose(m_window->glfw_window(), true);
				}
				break;
				}
			}
			catch (const std::bad_any_cast& e)
			{
				// Handle the error, e.g., log it or ignore the event
				LOG_ERROR(std::format("Failed to cast event arguments for KeyPressed event: {}", e.what()));
			}
		}
		break;
		}
	}
}