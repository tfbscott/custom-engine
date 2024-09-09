#pragma once
#include "dlldef.h"
#include <string>

namespace Tools
{

	//RETURNS AN ALLOCATED CHUNK OF MEMORY, MUST DELETE
	CE_CORELIB_API char* ReadFile(const char* name);


	CE_CORELIB_API void ConsoleWrite(const char* name);
}