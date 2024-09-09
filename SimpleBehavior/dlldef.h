#pragma once

#ifdef CE_BEHLIB_EXPORTS
#define CE_BEHLIB_API __declspec(dllexport)
#else
#define CE_BEHLIB_API __declspec(dllimport)
#endif