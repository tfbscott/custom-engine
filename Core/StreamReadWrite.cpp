#include "pch.h"
#include "StreamReadWrite.h"
#include <iostream>
#include <fstream>

namespace Tools
{

	std::string ReadFile(const char* name)
	{
		std::ifstream file;
		//Open
		file.open(name, std::ios_base::binary);

		//check if failed to open
		if (file.fail())
		{
			ConsoleWrite("Failed to open file of name");
			ConsoleWrite(name);
			return std::string();
		}

		//Seek to end of the file
		file.seekg(0, std::ios_base::end);
		//Get the length of the file
		long long length = file.tellg();
		//Jump back to the front
		file.seekg(0, std::ios_base::beg);

		char* data = new char[length + (long long)1];
		file.read(data, length);
		//Close the file
		file.close();

		//End the data will a null character
		data[length] = char(0);

		std::string dataString = std::string(data);

		delete[] data;

		return dataString;
	}


	void ConsoleWrite(const char* name)
	{
		std::cout << name << std::endl;
	}
}