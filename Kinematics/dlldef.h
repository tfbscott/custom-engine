#pragma once

#ifdef CE_KINELIB_EXPORTS
#define CE_KINELIB_API __declspec(dllexport)
#else
#define CE_KINELIB_API __declspec(dllimport)
#endif
