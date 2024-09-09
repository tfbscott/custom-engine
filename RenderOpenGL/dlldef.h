#pragma once


#ifdef CE_RENDEROGL_EXPORTS
#define CE_RENDEROGL_API __declspec(dllexport)
#else
#define CE_RENDEROGL_API __declspec(dllimport)
#endif
