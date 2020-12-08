#include "Window.h"
#include "NTErrors.h"
#include <glfw3.h>

namespace NTCrystal {

	void windowResize(GLFWwindow *window, int width, int height);

	Window::Window() : 
		m_width(1280),
		m_height(960),
		m_mousePos(0.0f,0.0f)
	{
		for (int i = 0; i < MAX_KEYS; i++){
			m_keys[i] = false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++){
			m_mouseButtons[i] = false;
		}


	}

	Window::~Window(){
		glfwTerminate();
	}

	int Window::create(std::string title, int width, int height, unsigned int currentFlags) {

		m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		m_width = width;
		m_height = height;
		if (!m_window){
			fatalError("GLFW Coud not initalize Window");
		}
		/*
		Uint32 flags = GLFW_WI SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE) {
		flags |=	glfw;
		}
		if (currentFlags & FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
		}
		*/
		glfwMakeContextCurrent(m_window);
		if (glfwGetCurrentContext == NULL){
			fatalError("Failed to initalize curent GLFW contex");
		}
		glfwSetWindowSizeCallback(m_window, windowResize);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);
		glfwSwapInterval(0.0);
		if (glewInit() != GLEW_OK){
			fatalError("Failed to initalize GLEW.!!!!");
		}

		//Set the background color to blue
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //tells how to do blending

		//Check the OpenGL version
		std::printf("***  OpenGL Version: %s  ***\n", glGetString(GL_VERSION));

		return 0;
	}

	void Window::clear(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() {
		glfwPollEvents();
		glfwGetWindowSize(m_window, &m_width, &m_height);
		glfwSwapBuffers(m_window);

	}

	bool Window::closed(){
		return glfwWindowShouldClose(m_window) == 1;
	}

	bool Window::isKeyPressed(unsigned int keyCode){
		if (keyCode >= MAX_KEYS){
			return false;
		}
		return m_keys[keyCode];
		
	}

	bool Window::isMouseButtonPressed(unsigned int keyCode){
		if (keyCode >= MAX_BUTTONS){
			return false;
		}
		return m_mouseButtons[keyCode];
	}

	void windowResize(GLFWwindow *window, int width, int height){
		//glfwGetFramebufferSize(window, &width, height);
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
		Window *wind = (Window*)glfwGetWindowUserPointer(window);
		wind->m_keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
		Window *wind = (Window*)glfwGetWindowUserPointer(window);
		wind->m_mouseButtons[button] = action != GLFW_RELEASE; 
	}

	void cursor_position_callback(GLFWwindow *window, double xpos, double ypos){
		Window *wind = (Window*)glfwGetWindowUserPointer(window);
		wind->m_mousePos.x = xpos;
		wind->m_mousePos.y = ypos;
	}
}