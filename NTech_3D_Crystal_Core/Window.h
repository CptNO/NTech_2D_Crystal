#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm\glm.hpp>
#include <string>
#include "maths.h"
#include "vec2.h"

namespace NTCrystal {
#define MAX_KEYS	1024
#define MAX_BUTTONS	32

	namespace WindowFlags{
		enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };
	}

    class Window
    {
    public:
        Window();
        ~Window();
        int create(std::string windowTitle, int screenWidth, int screenHeight, unsigned int currentFlags);
		void clear();
        void update();
		bool closed();
        int getScreenWidth() const { return m_width; }
		int getScreenHeight() const { return m_height; }
		math::vec2 getMousePos() const{ return m_mousePos; }

		bool isKeyPressed(unsigned int keyCode);
		bool isMouseButtonPressed(unsigned int buttonCode);
    private:
        GLFWwindow *m_window;
        int m_width, m_height;
		bool m_closed;
		bool m_keys[MAX_KEYS];
		bool m_mouseButtons[MAX_BUTTONS];
		math::vec2 m_mousePos;
		friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
	};


}