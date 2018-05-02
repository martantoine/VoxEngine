#pragma once

#include <fstream>
#include <string>

inline std::string readTextFile(const char* path)
{
	std::ifstream file(path, std::ios::in);

	if (!file.is_open())
	{
		file.close();
		return std::string("Failed to open " + (std::string)path + " !\n");
	}

	std::string result, line;
	while (getline(file, line))
		result += line + '\n';

	file.close();
	return result;
}