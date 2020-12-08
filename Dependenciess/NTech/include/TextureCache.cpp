#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
	//AUTO repleaces return type like this here (std::map<std::string, GLTexture>::iterator)
	auto mit = _textureMap.find(texturePath);

	if (mit == _textureMap.end())
	{
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);

		//make_pair() repleaces this => std::pair<std::string, GLTexture> newPair(texturePath, newTexture);
		_textureMap.insert(make_pair(texturePath, newTexture));

		std::cout << "Loaded cached texture: " + texturePath + "\n";
		return newTexture;
	}

	std::cout << "Used texture: " + texturePath + "\n";
	return mit->second;
}

