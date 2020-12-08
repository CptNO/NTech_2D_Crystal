#pragma once
#include <unordered_map>
#include <glm\glm.hpp>

namespace NTCrystal{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCords(float x, float y);

		//Returns true if key is held down
		bool isKeyDown(unsigned int keyID);

		//Returns if hay was just pressed
		bool isKeyPressed(unsigned int keyID);


		//Getters
		glm::vec2 getMouseCords() const{ return m_mouseCords; }

	private:

		bool wasKeyDown(unsigned int keyID);

		glm::vec2 m_mouseCords;
		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previusKeyMap;
	};
}

