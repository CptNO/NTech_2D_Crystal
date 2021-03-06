#pragma once

#include "TextureCache.h"
#include <string>

class ResourceManager
{
public:
	static GLTexture getTexture(std::string texturePath);

	//checks last bound texture
	static GLuint boundTexture;

private:
	static TextureCache _textureCache;
};

