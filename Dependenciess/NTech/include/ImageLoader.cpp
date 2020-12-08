#include "ImageLoader.h"
#include "picoPNG.h"
#include "IoMenager.h"
#include "Errors.h"

GLTexture ImageLoader::loadPNG(std::string filePath)
{
	GLTexture texture = {};

	std::vector < unsigned char> in;

	std::vector<unsigned char> out;

	unsigned long width, height;

	if (IoMenager::readFileToBuffer(filePath, in) == false)
	{
		fatalError("Failed to load PNG to buffer");
	}

	int errorCode = decodePNG(out, width, height,  &(in[0]), in.size());
	if (errorCode != 0)
	{
		fatalError("Decode PNG failed with error: " + std::to_string(errorCode));
	}

	//generate open gl texture object
	glGenTextures(1, &(texture.id));

	//bind the texture to object
	glBindTexture(GL_TEXTURE_2D, texture.id);
	//upload pixels tto image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	//set texture parametars
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	//return coppy of texture data
	return texture;
}
