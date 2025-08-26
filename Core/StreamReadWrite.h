#pragma once
#include <string>
#include <list>

namespace Tools
{
	std::string ReadFile(const char* name);


	void ConsoleWrite(const char* name);

	std::list<std::string> ReadCSV(const char* name, char delimeter = ' ');
}