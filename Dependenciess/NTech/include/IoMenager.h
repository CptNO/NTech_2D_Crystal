#pragma once

#include <vector>

class IoMenager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
};

