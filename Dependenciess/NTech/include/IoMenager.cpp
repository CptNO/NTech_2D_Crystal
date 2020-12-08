#include "IoMenager.h"

#include <fstream>

bool IoMenager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	//seek to end
	file.seekg(0, std::ios::end);

	//Gets file size
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	//Reduce file size by any headder size
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);

	file.close();

	return true;

}
