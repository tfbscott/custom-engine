#pragma once


#ifdef CE_CORELIB_EXPORTS
#define CE_CORELIB_API __declspec(dllexport)
#else
#define CE_CORELIB_API __declspec(dllimport)
#endif