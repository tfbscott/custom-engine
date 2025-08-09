#pragma once
#include <string>

namespace Tools
{

	//RETURNS AN ALLOCATED CHUNK OF MEMORY, MUST DELETE
	char* ReadFile(const char* name);


	void ConsoleWrite(const char* name);
}