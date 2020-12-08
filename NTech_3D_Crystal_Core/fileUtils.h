#pragma once
#include "common\pch.h"

namespace NTCrystal{
	
	class FileUtils
	{
		public:
			static std::string read_file(const char *filepath)
			{
				FILE *file = fopen(filepath, "rt");
				fseek(file, 0, SEEK_END);
				unsigned long leinght = ftell(file);
				char *data = new char[leinght + 1];
				memset(data, 0, leinght + 1);
				fseek(file, 0, SEEK_SET);
				fread(data, 1, leinght, file);
				fclose(file);

				std::string resault(data);
				delete[] data;
				return resault;
			}
	};
}