#pragma once
#include "dlldef.h"

namespace Component
{
	class Texture
	{
	public:

		CE_RENDEROGL_API Texture();

		CE_RENDEROGL_API void Read(const char* n, bool flip = false);

		void BindTexture();

		void UnbindTexture();

	private:
		int width;

		int height;

		int colorChannels;

		unsigned int textureID;
	};
}