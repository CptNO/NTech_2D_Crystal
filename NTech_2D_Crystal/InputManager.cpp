#include "InputManager.h"

namespace NTCrystal{

	InputManager::InputManager() : m_mouseCords(0,0)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update()
	{
		//look through key map and copy it to previus
		for each (auto &it in m_keyMap){
			m_previusKeyMap[it.first] = it.second;
		}
	}

	void InputManager::pressKey(unsigned int keyID)
	{
		m_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		m_keyMap[keyID] = false;
	}

	void InputManager::setMouseCords(float x, float y)
	{
		m_mouseCords.x = x;
		m_mouseCords.y = y;
	}

	bool InputManager::isKeyDown(unsigned int keyID)
	{
		auto it = m_keyMap.find(keyID);
		if (it != m_keyMap.end())
		{
			return it->second;
		}
		else
			return false;

	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		//check if it pressed this frame and not pressed
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false)
		{
			return true;
		}
		return false;
	}

	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = m_previusKeyMap.find(keyID);
		if (it != m_previusKeyMap.end())
		{
			return it->second;
		}
		else
			return false;
	}

}